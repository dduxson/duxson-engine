#include "CollisionSystem.h"

CollisionSystem::CollisionSystem(Maze::SPtr maze)
	: m_maze(maze)
{
	setupWallArrays();
}

void CollisionSystem::addMazeEntity(DE::IEntity::SPtr entity, bool collidable)
{
	if (entity == NULL)
		return;

	sf::Lock lock(m_mutex);

	if (collidable)
	{
		//Don't allow the same pointer twice in this list.
		for (std::list<DE::IEntity::SPtr>::iterator itr = m_entites.begin(); itr != m_entites.end(); ++itr)
		{
			if ((*itr) == entity)
				return;
		}

		m_entites.push_back(entity);
	}
	else
	{
		//Don't allow the same pointer twice in this list.
		for (std::list<DE::IEntity::SPtr>::iterator itr = m_nonCollidableEntites.begin(); itr != m_nonCollidableEntites.end(); ++itr)
		{
			if ((*itr) == entity)
				return;
		}

		m_nonCollidableEntites.push_back(entity);
	}
}

void CollisionSystem::removeMazeEntity(DE::IEntity::SPtr entity)
{
	if (entity == NULL)
		return;

	sf::Lock lock(m_mutex);

	//Check collidable list.
	for (std::list<DE::IEntity::SPtr>::iterator itr = m_entites.begin(); itr != m_entites.end(); ++itr)
	{
		if ((*itr) == entity)
		{
			itr = m_entites.erase(itr);
			return;
		}
	}

	//Check non collidable list.
	for (std::list<DE::IEntity::SPtr>::iterator itr = m_nonCollidableEntites.begin(); itr != m_nonCollidableEntites.end(); ++itr)
	{
		if ((*itr) == entity)
		{
			itr = m_nonCollidableEntites.erase(itr);
			return;
		}
	}
}

void CollisionSystem::removeAllEntites()
{
	sf::Lock lock(m_mutex);
	m_entites.clear();
	m_nonCollidableEntites.clear();
}

void CollisionSystem::setupWallArrays()
{
	//Setup lists of walls.
	m_allWalls.push_back(MazeCell::eWallLocationTop);
	m_allWalls.push_back(MazeCell::eWallLocationBottom);
	m_allWalls.push_back(MazeCell::eWallLocationLeft);
	m_allWalls.push_back(MazeCell::eWallLocationRight);
	m_verticalWalls.push_back(MazeCell::eWallLocationLeft);
	m_verticalWalls.push_back(MazeCell::eWallLocationRight);
	m_horizontalWalls.push_back(MazeCell::eWallLocationTop);
	m_horizontalWalls.push_back(MazeCell::eWallLocationBottom);
}

bool CollisionSystem::checkAndSetLocation(DE::IEntity::SPtr entity, glm::vec3& loc, bool checkMazeWalls, bool collideWithEntites, bool allowInStartEnd)
{
	if (entity == NULL)
		return false;

	bool moveX = true;
	bool moveZ = true;
	glm::vec3 currentLocation = entity->getWorldTransform().getTrans();
	glm::vec3 xProposedPos;

	//Check walls first.
	if (checkMazeWalls && m_maze && m_maze->isMazeGenerated())
	{
		// Move in x first
		// Get the cell of the maze we are in to determine what walls we have the potential to collide with.
		xProposedPos = glm::vec3(loc.x, currentLocation.y, currentLocation.z);
		float proposedCelRow = (-xProposedPos.z) / m_maze->getTotalCellLength();
		float proposedCelCol = xProposedPos.x / m_maze->getTotalCellLength();

		unsigned int row = unsigned int(proposedCelRow);
		unsigned int col = unsigned int(proposedCelCol);

		if (checkForWallCollision(entity, xProposedPos, row, col, m_allWalls) ||
			checkForWallCollision(entity, xProposedPos, row + 1, col, m_verticalWalls) ||
			checkForWallCollision(entity, xProposedPos, row - 1, col, m_verticalWalls) ||
			checkForWallCollision(entity, xProposedPos, row, col + 1, m_horizontalWalls) ||
			checkForWallCollision(entity, xProposedPos, row, col - 1, m_horizontalWalls))
		{
			loc.x = currentLocation.x;
			moveX = false;
		}

		//Now Move in z
		proposedCelRow = (-loc.z) / m_maze->getTotalCellLength();
		proposedCelCol = loc.x / m_maze->getTotalCellLength();

		row = unsigned int(proposedCelRow);
		col = unsigned int(proposedCelCol);

		if (checkForWallCollision(entity, loc, row, col, m_allWalls) ||
			checkForWallCollision(entity, loc, row + 1, col, m_verticalWalls) ||
			checkForWallCollision(entity, loc, row - 1, col, m_verticalWalls) ||
			checkForWallCollision(entity, loc, row, col + 1, m_horizontalWalls) ||
			checkForWallCollision(entity, loc, row, col - 1, m_horizontalWalls))
		{
			loc.z = currentLocation.z;
			moveZ = false;
		}
	}

	//Check entites
	if (collideWithEntites && (moveX || moveZ))
	{
		sf::Lock lock(m_mutex);
		for (std::list<DE::IEntity::SPtr>::iterator itr = m_entites.begin(); itr != m_entites.end(); ++itr)
		{
			//Ignore ourselves
			if ((*itr) == entity)
				continue;

			//Move in x first.
			xProposedPos = glm::vec3(loc.x, currentLocation.y, currentLocation.z);
			if (moveX && checkForEntityCollision(entity, xProposedPos, (*itr)))
			{
				loc.x = currentLocation.x;
				moveX = false;
			}
			//Now Move in Z
			if (moveZ && checkForEntityCollision(entity, loc, (*itr)))
			{
				loc.z = currentLocation.z;
				moveZ = false;
			}

		}
	}

	//Check start and end cells
	if ((!allowInStartEnd))
	{
		//Move x first
		if (moveX)
		{
			unsigned int proposedRow = unsigned int((-currentLocation.z) / m_maze->getTotalCellLength());
			unsigned int proposedCol = unsigned int(loc.x / m_maze->getTotalCellLength());
			MazeCell::SPtr cell = m_maze->getMazeCell(proposedRow, proposedCol);
			if (cell && (cell->isEndCell() || cell->isStartCell()))
			{
				loc.x = currentLocation.x;
				moveX = false;
			}
		}

		//Now move in z
		if (moveZ)
		{
			unsigned int proposedRow = unsigned int((-loc.z) / m_maze->getTotalCellLength());
			unsigned int proposedCol = unsigned int(loc.x / m_maze->getTotalCellLength());
			MazeCell::SPtr cell = m_maze->getMazeCell(proposedRow, proposedCol);
			if (cell && (cell->isEndCell() || cell->isStartCell()))
			{
				loc.z = currentLocation.z;
				moveZ = false;
			}
		}

	}

	if (moveX && moveZ)
		return true;

	return false;
}

DE::BoundingBox CollisionSystem::getEntityAABoundingBox(DE::IEntity::SPtr entity)
{
	if (entity == NULL)
		return DE::BoundingBox();

	DE::BoundingBox localSpaceBB = entity->getBoundingBox();
	glm::vec3 worldPos = entity->getWorldTransform().getTrans();

	glm::vec3 orientation = glm::eulerAngles(entity->getWorldTransform().getRot());
	float horAngleDegrees = fabs(fmod(glm::degrees(orientation.y), 360.0f));

	glm::vec3 worldBoxMin = localSpaceBB.getMin() + worldPos;
	glm::vec3 worldBoxMax = localSpaceBB.getMax() + worldPos;

	DE::BoundingBox aabb(worldBoxMin, worldBoxMax);

	//We can get away with a simple approximation for orientation in this game.
	if (horAngleDegrees > 45.0f && horAngleDegrees <= 135.0f ||
		horAngleDegrees > 225.0f && horAngleDegrees <= 315.0f)
	{
		float minX = aabb.getCenter().x - (aabb.getLength() / 2.0f);
		float minZ = aabb.getCenter().z - (aabb.getWidth() / 2.0f);

		float maxX = aabb.getCenter().x + (aabb.getLength() / 2.0f);
		float maxZ = aabb.getCenter().z + (aabb.getWidth() / 2.0f);

		return DE::BoundingBox(glm::vec3(minX, worldBoxMin.y, minZ), glm::vec3(maxX, worldBoxMax.y, maxZ));
	}
	else
	{
		return aabb;
	}
}

bool CollisionSystem::checkForEntityCollision(DE::IEntity::SPtr entity, glm::vec3 &proposedPos, DE::IEntity::SPtr otherEntity)
{
	if (entity == NULL || otherEntity == NULL)
		return false;

	glm::vec3 posDiff = proposedPos - entity->getWorldTransform().getTrans();

	DE::BoundingBox currentBox = getEntityAABoundingBox(entity);
	DE::BoundingBox proposedBox(currentBox.getMin() + posDiff, currentBox.getMax() + posDiff);

	//Check if proposed box intersects other entity.
	if (proposedBox.checkAABoundingBoxesIntersect(getEntityAABoundingBox(otherEntity)))
		return true;

	return false;
}

bool CollisionSystem::checkForWallCollision(DE::IEntity::SPtr entity, glm::vec3 &proposedPos, unsigned int row, unsigned int col, std::vector<MazeCell::WallLocation>& wallsToCheck)
{
	if (entity == NULL || m_maze == NULL)
		return false;

	//Get cell.
	MazeCell::SPtr cell = m_maze->getMazeCell(row, col);
	if (cell == NULL || wallsToCheck.size() == 0)
		return false;

	glm::vec3 posDiff = proposedPos - entity->getWorldTransform().getTrans();

	DE::BoundingBox currentBox = getEntityAABoundingBox(entity);
	DE::BoundingBox proposedBox(currentBox.getMin() + posDiff, currentBox.getMax() + posDiff);
	DE::BoundingBox wallBox;

	float cellLength = m_maze->getTotalCellLength();
	float wallHeight = m_maze->getMazeWallHeight();
	float wallThickness = m_maze->getMazeWallThickness();
	float halfWallThickness = wallThickness * 0.5f;

	//Loop through walls to check for this cell
	for (unsigned int i = 0; i < wallsToCheck.size(); ++i)
	{
		//Find wall rect
		if (wallsToCheck[i] == MazeCell::eWallLocationTop && cell->getWallStatus(MazeCell::eWallLocationTop))
		{
			glm::vec3 min((float(col) * cellLength) - (halfWallThickness), 0.0f, -float(row + 1) * cellLength - (halfWallThickness));
			glm::vec3 max(min.x + cellLength + wallThickness, wallHeight, min.z + wallThickness);

			wallBox = DE::BoundingBox(min, max);
		}
		else if (wallsToCheck[i] == MazeCell::eWallLocationBottom && cell->getWallStatus(MazeCell::eWallLocationBottom))
		{
			glm::vec3 min((float(col) * cellLength) - (halfWallThickness), 0.0f, -float(row) * cellLength - (halfWallThickness));
			glm::vec3 max(min.x + cellLength + wallThickness, wallHeight, min.z + wallThickness);

			wallBox = DE::BoundingBox(min, max);
		}
		else if (wallsToCheck[i] == MazeCell::eWallLocationLeft && cell->getWallStatus(MazeCell::eWallLocationLeft))
		{
			glm::vec3 min((float(col) * cellLength) - (halfWallThickness), 0.0f, -float(row + 1) * cellLength - (halfWallThickness));
			glm::vec3 max(min.x + wallThickness, wallHeight, min.z + cellLength + wallThickness);

			wallBox = DE::BoundingBox(min, max);
		}
		else if (wallsToCheck[i] == MazeCell::eWallLocationRight && cell->getWallStatus(MazeCell::eWallLocationRight))
		{
			glm::vec3 min((float(col + 1) * cellLength) - (halfWallThickness), 0.0f, -float(row + 1) * cellLength - (halfWallThickness));
			glm::vec3 max(min.x + wallThickness, wallHeight, min.z + cellLength + wallThickness);

			wallBox = DE::BoundingBox(min, max);
		}

		//Check if proposed box intersects wall
		if (proposedBox.checkAABoundingBoxesIntersect(wallBox))
			return true;
	}

	return false;
}

bool CollisionSystem::areEntitiesInCell(unsigned int row, unsigned int col)
{
	glm::vec3 pos;
	unsigned int entityRow, entityCol;

	sf::Lock lock(m_mutex);

	//Check collidable.
	for (std::list<DE::IEntity::SPtr>::iterator itr = m_entites.begin(); itr != m_entites.end(); ++itr)
	{
		pos = (*itr)->getWorldTransform().getTrans();
		entityRow = unsigned int((-pos.z) / m_maze->getTotalCellLength());
		entityCol = unsigned int(pos.x / m_maze->getTotalCellLength());
		if (entityRow == row && entityCol == col)
			return true;
	}

	//Check non-collidable.
	for (std::list<DE::IEntity::SPtr>::iterator itr = m_nonCollidableEntites.begin(); itr != m_nonCollidableEntites.end(); ++itr)
	{
		pos = (*itr)->getWorldTransform().getTrans();
		entityRow = unsigned int((-pos.z) / m_maze->getTotalCellLength());
		entityCol = unsigned int(pos.x / m_maze->getTotalCellLength());
		if (entityRow == row && entityCol == col)
			return true;
	}

	return false;
}

std::list<DE::IEntity::SPtr> CollisionSystem::getCollidableEntitiesInCells(std::list<glm::vec2>& cellLocs)
{
	std::list<DE::Entity::SPtr> entityList;

	glm::vec3 pos;
	unsigned int entityRow, entityCol;

	sf::Lock lock(m_mutex);
	for (std::list<DE::IEntity::SPtr>::iterator itr = m_entites.begin(); itr != m_entites.end(); ++itr)
	{
		pos = (*itr)->getWorldTransform().getTrans();
		entityRow = unsigned int((-pos.z) / m_maze->getTotalCellLength());
		entityCol = unsigned int(pos.x / m_maze->getTotalCellLength());
		for (std::list<glm::vec2>::iterator itrLoc = cellLocs.begin(); itrLoc != cellLocs.end(); ++itrLoc)
			if ((entityRow == itrLoc->y) && (entityCol == itrLoc->x))
				entityList.push_back(*itr);
	}

	return entityList;
}

std::list<DE::IEntity::SPtr> CollisionSystem::getNonCollidableEntitiesInCells(std::list<glm::vec2>& cellLocs)
{
	std::list<DE::IEntity::SPtr> entityList;

	glm::vec3 pos;
	unsigned int entityRow, entityCol;

	sf::Lock lock(m_mutex);
	for (std::list<DE::IEntity::SPtr>::iterator itr = m_nonCollidableEntites.begin(); itr != m_nonCollidableEntites.end(); ++itr)
	{
		pos = (*itr)->getWorldTransform().getTrans();
		entityRow = unsigned int((-pos.z) / m_maze->getTotalCellLength());
		entityCol = unsigned int(pos.x / m_maze->getTotalCellLength());
		for (std::list<glm::vec2>::iterator itrLoc = cellLocs.begin(); itrLoc != cellLocs.end(); ++itrLoc)
			if ((entityRow == itrLoc->y) && (entityCol == itrLoc->x))
				entityList.push_back(*itr);
	}

	return entityList;
}

std::list<DE::IEntity::SPtr> CollisionSystem::doesEntityIntersectOthers(DE::IEntity::SPtr entity)
{
	std::list<DE::IEntity::SPtr> entitesIntersecting;

	//Loop through all entites and compare bounding boxes
	sf::Lock lock(m_mutex);

	DE::BoundingBox entityBB = getEntityAABoundingBox(entity);

	//Check collidable
	for (std::list<DE::IEntity::SPtr>::iterator itr = m_entites.begin(); itr != m_entites.end(); ++itr)
	{
		//Ignore ourselves
		if ((*itr) == entity)
			continue;

		if (entityBB.checkAABoundingBoxesIntersect(getEntityAABoundingBox(*itr)))
			entitesIntersecting.push_back((*itr));
	}

	//Check non-collidable
	for (std::list<DE::IEntity::SPtr>::iterator itr = m_nonCollidableEntites.begin(); itr != m_nonCollidableEntites.end(); ++itr)
	{
		//Ignore ourselves
		if ((*itr) == entity)
			continue;

		if (entityBB.checkAABoundingBoxesIntersect(getEntityAABoundingBox(*itr)))
			entitesIntersecting.push_back((*itr));
	}

	return entitesIntersecting;
}