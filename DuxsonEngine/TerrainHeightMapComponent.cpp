#include "./Include/TerrainHeightMapComponent.h"
#include "./Include/VisualEngine.h"
#include "./Include/Entity.h"
#include "./Include/Logger.h"
#include "./include/Geometry.h"
#include "./include/TextureParameters.h"
#include "./include/Model.h"
#include "./include/Mesh.h"
#include "./include/Material.h"
#include <SFML/Graphics/Image.hpp>

namespace DE
{
	TerrainHeightMapComponent::TerrainHeightMapComponent(const std::string& heightMapFilename, const std::string& textureFilename, IShaderProgram::SPtr prog,
		unsigned int texXRepeatPxls, unsigned int texYRepeatPxls)
		: ModelVisualEntityComponent()
	{
		m_shaderProgram = prog;

		//Load the height map image.
		sf::Image image;

		if (!image.loadFromFile(heightMapFilename))
		{
			Logger::Instance()->writeToLogFile(Logger::eLogError, "Failed to load height map image with name: %s", heightMapFilename.c_str());
		}
		else
		{
			Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Sucessfully loaded height map image with name: %s", heightMapFilename.c_str());

			//Generate Data from image
			sf::Vector2u imageSize = image.getSize();
			std::vector< std::vector<glm::vec2> > texCoords;
			std::vector< std::vector<glm::vec3> > normals;

			generateVerticesAndTexCoords(image, m_vertices, texCoords, texXRepeatPxls, texYRepeatPxls);

			//Create Geometry for Data
			std::vector<glm::vec3> geomVertices;
			std::vector<glm::vec2> geomTexCoords;
			std::vector<unsigned int> geomIndicies;

			for (unsigned int x = 0; x < imageSize.x; ++x)
			{
				for (unsigned int y = 0; y < imageSize.y; ++y)
				{
					geomVertices.push_back(m_vertices[x][y]);
					geomTexCoords.push_back(texCoords[x][y]);

					if (x < (imageSize.x - 1) && y < (imageSize.y - 1))
					{
						unsigned int added_factor = (x*imageSize.y);
						geomIndicies.push_back(y + added_factor);
						geomIndicies.push_back(y + 1 + added_factor);
						geomIndicies.push_back(imageSize.y + y + added_factor);
						geomIndicies.push_back(imageSize.y + y + added_factor);
						geomIndicies.push_back(y + 1 + added_factor);
						geomIndicies.push_back(imageSize.y + 1 + y + added_factor);
					}
				}
			}

			Geometry::SPtr geometry = std::make_shared<Geometry>(geomIndicies, geomVertices, geomTexCoords);
			geometry->finalizeGeom();

			TextureParams texParams(textureFilename);
			texParams.clamp = false;

			//Create the model and material to render.
			m_model = std::make_shared<Model>(std::make_shared<Mesh>(heightMapFilename, geometry), std::make_shared<Material>(texParams));
		}
	}

	void TerrainHeightMapComponent::generateVerticesAndTexCoords(const sf::Image& image, std::vector< std::vector<glm::vec3> >& vertices, std::vector< std::vector<glm::vec2> >& texCoords,
		unsigned int texXRepeatPxls, unsigned int texYRepeatPxls)
	{
		//(height calculated using red channel)
		sf::Vector2u imageSize = image.getSize();

		for (unsigned int x = 0; x < imageSize.x; ++x)
		{
			vertices.push_back(std::vector<glm::vec3>(imageSize.y));
			texCoords.push_back(std::vector<glm::vec2>(imageSize.y));
		}

		//Repeat the texture every so often.
		float texScaleX = imageSize.x / float(texXRepeatPxls);
		float texScaleY = imageSize.y / float(texYRepeatPxls);

		for (unsigned int x = 0; x < imageSize.x; ++x)
		{
			for (unsigned int y = 0; y < imageSize.y; ++y)
			{
				float xScale = float(x) / float(imageSize.x - 1);
				float yScale = float(y) / float(imageSize.y - 1);
				float vertexHeight = float(image.getPixel(x, y).r) / 255.0f;

				vertices[x][y] = glm::vec3(xScale, vertexHeight, yScale);
				texCoords[x][y] = glm::vec2(xScale*texScaleX, yScale*texScaleY);
			}
		}
	}

	TerrainHeightMapComponent::~TerrainHeightMapComponent()
	{
	}

	void TerrainHeightMapComponent::render(IVisualEngine::SPtr visualEngine) const
	{
		ModelVisualEntityComponent::render(visualEngine);
	}

	double TerrainHeightMapComponent::getWorldHeight(double x, double z)
	{
		if (!m_parent.expired() && m_vertices.size() > 0)
		{
			const Transform& world_transform = m_parent.lock()->getWorldTransform();
			glm::vec3 scale = world_transform.getScale();
			glm::vec3 trans = world_transform.getTrans();

			//TODO What if we have rotated? For now assume we haven't!
			double terrainX = x - trans.x;
			double terrainZ = z - trans.z;

			double gridXSize = scale.x / double(m_vertices.size() - 1);
			double gridZSize = scale.z / double(m_vertices[0].size() - 1);

			int gridX = int(floor(terrainX / gridXSize));
			int gridZ = int(floor(terrainZ / gridZSize));

			if (gridX < 0 || gridZ < 0 || gridX >= int(m_vertices.size()) || gridZ >= int(m_vertices[gridX].size()))
				return -1.0;

			//Coordinate between 0 and 1 in the grid square.
			double xCoord = fmod(terrainX, gridXSize) / gridXSize;
			double zCoord = fmod(terrainZ, gridZSize) / gridZSize;
			double yCoord = 0.0;

			//Which triangle of the grid square are we in?
			if (xCoord <= 1 - zCoord)
			{
				yCoord = barryCentricInterpolation(glm::vec3(0, m_vertices[gridX][gridZ].y, 0),
					glm::vec3(1, m_vertices[gridX + 1][gridZ].y, 0),
					glm::vec3(0, m_vertices[gridX][gridZ + 1].y, 1),
					glm::vec2(xCoord, zCoord));
			}
			else
			{
				yCoord = barryCentricInterpolation(glm::vec3(1, m_vertices[gridX + 1][gridZ].y, 0),
					glm::vec3(1, m_vertices[gridX + 1][gridZ + 1].y, 1),
					glm::vec3(0, m_vertices[gridX][gridZ + 1].y, 1),
					glm::vec2(xCoord, zCoord));
			}

			return yCoord * scale.y;
		}

		return -1.0;
	}

	double TerrainHeightMapComponent::barryCentricInterpolation(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, const glm::vec2& pos)
	{
		double det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
		double l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
		double l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
		double l3 = 1.0f - l1 - l2;
		return l1 * p1.y + l2 * p2.y + l3 * p3.y;
	}
}
