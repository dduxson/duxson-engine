#include "MazeEntityComponent.h"

MazeEntityComponent::MazeEntityComponent()
	: VisualEntityComponent()
	, m_maze(NULL)
	, m_currentCell(NULL)
	, m_collisionSystem(NULL)
	, m_collideWithWalls(true)
	, m_collideWithEntites(true)
	, m_allowInStartEndCells(true)
{
	float sqrt3 = sqrtf(3.0f);
	m_velocity = glm::vec3(7.0f / sqrt3, 7.0f / sqrt3, 7.0f / sqrt3); //(Speed of 7)
}

MazeEntityComponent::~MazeEntityComponent()
{
	m_maze = NULL;
}

void MazeEntityComponent::setMazeIn(Maze::SPtr maze)
{
	if (maze != NULL)
		m_maze = maze;
}

bool MazeEntityComponent::setCurrentLocation(glm::vec3& loc, bool checkForCollisions)
{
	bool success = true;

	DE::IEntity::SPtr parent = m_parent.lock();

	if (checkForCollisions && m_maze && parent && m_maze->isMazeGenerated() && m_collisionSystem)
	{
		success = m_collisionSystem->checkAndSetLocation(parent, loc, m_collideWithWalls, m_collideWithEntites, m_allowInStartEndCells);
	}

	//Set the new position in the maze.
	if(parent != nullptr)
		parent->setWorldTrans(loc);

	if (m_maze)
		m_currentCell = m_maze->getMazeCell(unsigned int((-loc.z) / m_maze->getTotalCellLength()), unsigned int(loc.x / m_maze->getTotalCellLength()));

	return success;
}

bool MazeEntityComponent::setCurrentRotation(glm::quat& rot, bool checkForCollisions)
{
	bool success = true;

	DE::IEntity::SPtr parent = m_parent.lock();

	if (checkForCollisions && m_collisionSystem && parent != nullptr)
	{
		glm::vec3 trans = parent->getWorldTransform().getTrans();
		success = m_collisionSystem->checkAndSetLocation(parent, trans, m_collideWithWalls, m_collideWithEntites, m_allowInStartEndCells);
	}

	if(parent != nullptr)
		parent->setWorldRot(rot);

	return success;
}

MazeCell::SPtr MazeEntityComponent::getCurrentMazeCell()
{
	return m_currentCell;
}

Maze::SPtr MazeEntityComponent::getMazeIn() const
{
	return m_maze;
}

void MazeEntityComponent::setVelocity(const glm::vec3& vel)
{
	m_velocity = vel;
}

glm::vec3 MazeEntityComponent::getCurrentVelocity()
{
	return m_velocity;
}

float MazeEntityComponent::getSpeed()
{
	return glm::length(m_velocity);
}

void MazeEntityComponent::setCollidableWithWalls(bool collidable)
{
	m_collideWithWalls = collidable;
}

void MazeEntityComponent::setAllowedInStartEndCells(bool allowed)
{
	m_allowInStartEndCells = allowed;
}

void MazeEntityComponent::setCollidableWithEntites(bool collidable)
{
	m_collideWithEntites = collidable;
}

void MazeEntityComponent::setCollisionSystem(CollisionSystem::SPtr collisionSystem)
{
	m_collisionSystem = collisionSystem;
}

CollisionSystem::SPtr MazeEntityComponent::getCollisionSystem()
{
	return m_collisionSystem;
}