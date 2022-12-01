#pragma once
/*!********************************************************************
*	File:	CollisionSystem.h
*
* \brief	A basic collision system for maze entites that
*			are in the the maze.
*
* \details It will only check the required adjacent cells
*			of the maze to save time on checks that are not required.
*			Walls and entities supplied can be checked.
*			This class has been made thread safe as entities may be
*			added or removed by different threads.
*			All entites given to this system should be in the same
*			maze.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include "../DuxsonEngine/Include/Entity.h"
#include <SFML/System.hpp>
#include "Maze.h"
#include "MazeCell.h"
#include <vector>
#include <list>

class CollisionSystem
{
	public:
		typedef std::shared_ptr<CollisionSystem> SPtr;

		/*!
		*	\brief	Constructor for CollisionSystem class.
		*/
		CollisionSystem(Maze::SPtr maze);

		/*!
		*	\brief	Adds an entity to the collision system.
		*	\param[in]	entity		A pointer to a MazeEntity you wish to add.
		*	\param[in]	collidable	Set to true if this entity cannot be gone through.
		*/
		void addMazeEntity(DE::IEntity::SPtr entity, bool collidable);

		/*!
		*	\brief	Removes an entity from the collision system.
		*	\param[in]	entity		A pointer to a MazeEntity you wish to remove.
		*/
		void removeMazeEntity(DE::IEntity::SPtr entity);

		/*!
		*	\brief	Removes all entities that both collidable and non collidable
		*			from the collision system.
		*/
		void removeAllEntites();

		/*!
		*	\brief	Checks if there are entities in a cell in the maze.
		*	\param[in] row The row of cell to check (0 based index).
		*	\param[in] col The column of the cell to check (0 based index).
		*	\return True if there is one or more entities in the cell of the row and
		*			column specified. False otherwise.
		*/
		bool areEntitiesInCell(unsigned int row, unsigned int col);

		/*!
		*	\brief	Checks a location as to whether this is allowed and will set the
		*			second parameter to the nearest location allowed.
		*	\remark X and Z axes are checked seperatly.
		*	\param[in]	entity			Pointer to the enitity you wish to move.
		*	\param[in]	loc				The proposed location - this will also become the closest
		*								allowed location after collision detection.
		*	\param[in]	checkMazeWalls	Whether to check collisions with maze walls.
		*	\param[in]	collideWithEntites Whether to check collision with other entites.
		*	\param[in]	allowInStartEnd Whether we are allowed in start and end cells.
		*	\return		Whether the proposed Location was allowed in all x,y and z.
		*/
		bool checkAndSetLocation(DE::IEntity::SPtr entity, glm::vec3& loc, bool checkMazeWalls, bool collideWithEntites, bool allowInStartEnd);

		/*!
		*	\brief	Checks if the supplied entity overlaps any other entities.
		*	\param[in] entity Pointer to the MazeEntity you wish to see if any other
		*					  entites known to the collision system overlap with.
		*	\return Array of pointers to MazeEntitys that overlap the entity supplied.
		*			This will have a size zero if known overlap.
		*	\remark This function should be used to check if non collidable entites overlap
		*			others.
		*/
		std::list<DE::IEntity::SPtr> doesEntityIntersectOthers(DE::IEntity::SPtr entity);

		/*!
		*	\brief	Gets the collidable entites that are present in a cell.
		*	\param[in] cellLoc List of vec2s where x=col and y=row to check.
		*	\return A list of the collidable maze entites that are present in the cells.
		*/
		std::list<DE::Entity::SPtr> getCollidableEntitiesInCells(std::list<glm::vec2>& cellLocs);

		/*!
		*	\brief	Gets the non collidable entites that are present in a cell.
		*	\param[in] cellLoc List of vec2s where x=col and y=row to check.
		*	\return A list of the non collidable maze entites that are present in the cell.
		*/
		std::list<DE::IEntity::SPtr> getNonCollidableEntitiesInCells(std::list<glm::vec2>& cellLocs);

	private:
		/*!
		*	\brief	Sets up arrays of wall locations.
		*/
		void setupWallArrays();

		/*!
		*	\brief		Checks whether the proposedPos will cause the MazeEntity to intersect any walls within a maze cell
		*	\param[in]	entity			Pointer to the enitity you wish to move.
		*	\param[in]	proposedPos		The proposed position of the MazeEntity in x and z. y coordinate is ignored.
		*	\param[in]	row				The row of the maze cell to check
		*	\param[in]	col				The column of the maze cell to check
		*	\param[in]	wallsToCheck	A vector of the walls of the cell we should check.
		*	\remark		The MazeEntity is assumed to be a rectangle.
		*	\return		True if collide with wall, false otherwise.
		*/
		bool checkForWallCollision(DE::IEntity::SPtr entity, glm::vec3 &proposedPos, unsigned int row, unsigned int col, std::vector<MazeCell::WallLocation>& wallsToCheck);

		/*!
		*	\brief		Checks whether the proposedPos will cause the MazeEntity to intersect another entity.
		*	\param[in]	entity			Pointer to the enitity you wish to move.
		*	\param[in]	proposedPos		The proposed position of the MazeEntity in x and z. y coordinate is ignored.
		*	\param[in]	otherEntity		Pointer to the other entity you wish to check if entity intersects at the proposed pos.
		*	\return		True if collide with other entity, false otherwise.
		*/
		bool checkForEntityCollision(DE::IEntity::SPtr entity, glm::vec3 &proposedPos, DE::IEntity::SPtr otherEntity);

		/*!
		*	\brief	Gets the axis aligned bounding box of the given MazeEntity.
		*	\return	The axis aligned bounding box of the given MazeEntity.
		*/
		DE::BoundingBox getEntityAABoundingBox(DE::IEntity::SPtr entity);

	private:
		sf::Mutex							m_mutex;				///< Mutex lock for changing entities lists.
		Maze::SPtr							m_maze;					///< The maze in which all entities reside.
		std::vector<MazeCell::WallLocation>	m_allWalls;				///< All locations of walls that can be collided with.
		std::vector<MazeCell::WallLocation>	m_verticalWalls;		///< Vertical locations of walls that can be collided with.
		std::vector<MazeCell::WallLocation>	m_horizontalWalls;		///< Horizontal locations of walls that can be collided with.
		std::list<DE::IEntity::SPtr>		m_entites;				///< Entities that other entites can collide with.
		std::list<DE::IEntity::SPtr>		m_nonCollidableEntites;	///< Entities that other entites can go through.

};