#include "../DuxsonEngine/Include/Model.h"
#include "../DuxsonEngine/Include/LineWidth.h"
#include "../DuxsonEngine/Include/ModelVisualEntityComponent.h"
#include "../DuxsonEngine/include/Mesh.h"
#include "../DuxsonEngine/include/ShaderProgram.h"
#include "TwoDMazeEntityBuilder.h"

TwoDMazeEntityBuilder::TwoDMazeEntityBuilder()
	: IMazeEntityBuilder()
	, m_width(1.0f)
	, m_height(1.0f)
	, m_lineWidth(4.0f)
	, m_lineColour(0.0f, 0.0f, 0.5f, 1.0f)
{

}

TwoDMazeEntityBuilder::~TwoDMazeEntityBuilder()
{

}

void TwoDMazeEntityBuilder::setWidth(float width)
{
	m_width = width;
}

void TwoDMazeEntityBuilder::setHeight(float height)
{
	m_height = height;
}

void TwoDMazeEntityBuilder::setWallLineParams(float width, const glm::vec4& col)
{
	m_lineWidth = width;
	m_lineColour = col;
}

DE::Entity::SPtr TwoDMazeEntityBuilder::generateEntity(const Maze &maze)
{
	DE::Entity::SPtr mazeEntity = std::make_shared<DE::Entity>();
	mazeEntity->setAbsoluteCoords(true);

	std::vector<glm::vec3> verts;
	std::vector<glm::vec4> colours;

	unsigned int numOfCols = maze.getNumOfCols();
	unsigned int numOfRows = maze.getNumOfRows();

	//Calculate vertices for each of the walls.
	float twoDCellWidth = m_width / float(numOfCols);
	float twoDCellHeight = m_height / float(numOfRows);

	for (unsigned int row = 0; row < numOfRows; row++)
	{
		for (unsigned int col = 0; col < numOfCols; col++)
		{
			MazeCell::SPtr cell = maze.getMazeCell(row, col);

			if (cell == NULL)
				continue;

			//Always put up left
			if (cell->getWallStatus(MazeCell::eWallLocationLeft))
			{
				verts.push_back(glm::vec3(twoDCellWidth*col, twoDCellHeight * row, 0.0));
				verts.push_back(glm::vec3(twoDCellWidth*col, twoDCellHeight *(row + 1), 0.0));
				colours.push_back(glm::vec4(m_lineColour));
				colours.push_back(glm::vec4(m_lineColour));
			}

			//Put up right if on permieter
			if ((col == numOfCols - 1) && cell->getWallStatus(MazeCell::eWallLocationRight))
			{
				verts.push_back(glm::vec3(twoDCellWidth*(col + 1), twoDCellHeight*row, 0.0));
				verts.push_back(glm::vec3(twoDCellWidth*(col + 1), twoDCellHeight*(row + 1), 0.0));
				colours.push_back(glm::vec4(m_lineColour));
				colours.push_back(glm::vec4(m_lineColour));
			}

			//Always put up the top walls.
			if (cell->getWallStatus(MazeCell::eWallLocationTop))
			{
				verts.push_back(glm::vec3(twoDCellWidth*col, twoDCellHeight*(row + 1), 0.0));
				verts.push_back(glm::vec3(twoDCellWidth*(col + 1), twoDCellHeight*(row + 1), 0.0));
				colours.push_back(glm::vec4(m_lineColour));
				colours.push_back(glm::vec4(m_lineColour));
			}

			//Put up bottom walls around perimeter only.
			if ((row == 0) && cell->getWallStatus(MazeCell::eWallLocationBottom))
			{
				verts.push_back(glm::vec3(twoDCellWidth*col, twoDCellHeight*row, 0.0));
				verts.push_back(glm::vec3(twoDCellWidth*(col + 1), twoDCellHeight*row, 0.0));
				colours.push_back(glm::vec4(m_lineColour));
				colours.push_back(glm::vec4(m_lineColour));
			}
		}
	}

	DE::Geometry::SPtr mazeGeo = std::make_shared<DE::Geometry>(std::vector<unsigned int>(), verts, std::vector<glm::vec2>(), std::vector<glm::vec3>(), std::vector<glm::vec3>(), colours);
	mazeGeo->setGeometryType(DE::Geometry::eLineGeometry);

	DE::ModelVisualEntityComponent::SPtr visComp = std::make_shared<DE::ModelVisualEntityComponent>(std::make_shared<DE::Model>(std::make_shared<DE::Mesh>("2DMaze", mazeGeo), nullptr),
																									std::make_shared<DE::ShaderProgram>("./Data/Shaders/vertexColour.prog"));
	visComp->setRenderState(std::make_shared<DE::LineWidth>(m_lineWidth));
	mazeEntity->addComponent(visComp);

	return mazeEntity;
}