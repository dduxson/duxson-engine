#include "MapHUDBuilder.h"
#include "EntityFollow.h"
#include "../DuxsonEngine/Include/Model.h"
#include "../DuxsonEngine/Include/Mesh.h"
#include "../DuxsonEngine/Include/ShaderProgram.h"
#include "../DuxsonEngine/Include/ModelVisualEntityComponent.h"

MapHUDBuilder::MapHUDBuilder()
	: HUDBuilder()
	, m_entity(NULL)
{

}

MapHUDBuilder::~MapHUDBuilder()
{
	m_entity = NULL;
}

void MapHUDBuilder::setEntity(DE::Entity::SPtr entity)
{
	m_entity = entity;
}

DE::Entity::SPtr MapHUDBuilder::generateArrowEntity(float length, float width, const glm::vec4 &col)
{
	DE::Entity::SPtr arrowEntity = std::make_shared<DE::Entity>();

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec4> colours;

	float halfLength = length / 2.0f;
	float halfWidth = width / 2.0f;

	vertices.push_back(glm::vec3(-halfLength, halfWidth, 0.0f));
	vertices.push_back(glm::vec3(halfLength, 0.0f, 0.0f));
	vertices.push_back(glm::vec3(-halfLength, -halfWidth, 0.0f));

	colours.push_back(col);
	colours.push_back(col);
	colours.push_back(col);

	DE::Geometry::SPtr arrowGeo = std::make_shared<DE::Geometry>(std::vector<unsigned int>(), vertices, std::vector<glm::vec2>(), std::vector<glm::vec3>(), std::vector<glm::vec3>(), colours);

	DE::IMesh::SPtr mesh = std::make_shared<DE::Mesh>("HUDMapArrow", arrowGeo);
	DE::IModel::SPtr model = std::make_shared<DE::Model>(mesh, nullptr);
	arrowEntity->addComponent(std::make_shared<DE::ModelVisualEntityComponent>(model, std::make_shared<DE::ShaderProgram>("./Data/Shaders/vertexColour.prog")));

	return arrowEntity;
}

DE::Entity::SPtr MapHUDBuilder::generateEntity(const Maze &maze)
{
	DE::Entity::SPtr backgroundEntity = HUDBuilder::generateEntity(maze);

	if (backgroundEntity)
	{
		//Build maze and arrow to represent player.
		float cellSize = 0.2f;
		float mazeWidth = maze.getNumOfCols() * cellSize;
		float mazeHeight = maze.getNumOfRows() * cellSize;
		m_twoDMazeBuilder.setWidth(mazeWidth);
		m_twoDMazeBuilder.setHeight(mazeHeight);

		DE::Entity::SPtr	twoDMazeEntity = m_twoDMazeBuilder.generateEntity(maze);
		DE::Entity::SPtr	arrowEntity = generateArrowEntity(cellSize *0.5f, cellSize *0.25f, glm::vec4(1.0f, 1.0f, 0.2f, 1.0f));

		//Setup components to update the position and rotations of maze and arrow.
		if (m_entity)
		{
			EntityFollow::SPtr mazeEntityFollow = std::make_shared<EntityFollow>(m_entity);
			EntityFollow::SPtr arrowEntityFollow = std::make_shared<EntityFollow>(m_entity);

			float xMapIncrement = 1.0f / float(maze.getNumOfCols()*maze.getTotalCellLength());
			float yMapIncrement = 1.0f / float(maze.getNumOfRows()*maze.getTotalCellLength());

			mazeEntityFollow->setRotationOffset(glm::vec3(0.0f, 0.0f, 0.0f));
			mazeEntityFollow->setRotationScalar(glm::vec3(0.0f, 0.0f, 0.0f));
			mazeEntityFollow->setPositionScalar(glm::vec3(xMapIncrement * -mazeWidth, yMapIncrement * -mazeHeight, 0.0f));
			mazeEntityFollow->setPositionOffset(glm::vec3(0.5f, 0.5f, 0.0f));
			mazeEntityFollow->setTwoD(true);

			arrowEntityFollow->setRotationOffset(glm::vec3(0.0f, 0.0f, glm::radians(90.0f)));
			arrowEntityFollow->setRotationScalar(glm::vec3(1.0f, 0.0f, 1.0f));
			arrowEntityFollow->setPositionScalar(glm::vec3(xMapIncrement * mazeWidth, yMapIncrement * mazeHeight, 0.0f));
			arrowEntityFollow->setTwoD(true);

			twoDMazeEntity->addComponent(mazeEntityFollow);
			arrowEntity->addComponent(arrowEntityFollow);
		}

		backgroundEntity->addChild(twoDMazeEntity);
		twoDMazeEntity->addChild(arrowEntity);
	}

	return backgroundEntity;
}