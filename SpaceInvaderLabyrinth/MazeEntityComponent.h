#pragma once
/*!********************************************************************
*	File:	MazeEntityComponent.h
*
* \brief	Represents an entity in the maze. This could be a player
*			or an enemy.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include <glm/glm.hpp>
#include "Maze.h"
#include "CollisionSystem.h"
#include "../DuxsonEngine/Include/VisualEntityComponent.h"

class MazeEntityComponent : public DE::VisualEntityComponent
{
public:
	/*!
	*	\brief	Constructor for MazeEntityComponent class.
	*/
	MazeEntityComponent();

	/*!
	*	\brief	Destructor for MazeEntityComponent class.
	*/
	virtual ~MazeEntityComponent();

	/*!
	*	\brief	Set the maze that this MazeEntity is currently in.
	*	\param[in]	maze A pointer to the maze to put this MazeEntity in.
	*/
	void setMazeIn(Maze::SPtr maze);

	/*!
	*	\brief	Set the collision system to use.
	*	\param[in]	collisionSystem A pointer to the collision system to use.
	*/
	void setCollisionSystem(CollisionSystem::SPtr collisionSystem);

	/*!
	*	\brief	Set the collision system to use.
	*	\param[in]	collisionSystem A pointer to the collision system to use.
	*/
	CollisionSystem::SPtr getCollisionSystem();

	/*!
	*	\brief		Sets the current location of the MazeEntity. This will
	*				perform collision detection to only allow the MazeEntity
	*				to move where they should be able to (if the second
	*				parameter is true).
	*	\param[in]	loc Vec3 representing the location the MazeEntity should
	*					attempt to move to.
	*	\param[in]  checkForCollisions Set this to false should you not wish
	*				to check for collisions and force the MazeEntity to assume
	*				a position.
	*	\remark		You should call setMazeIn before this function initially.
	*	\return		True if we successfully set the position on all axes.
	*				False otherwise.
	*/
	virtual bool setCurrentLocation(glm::vec3& loc, bool checkForCollisions = true);

	/*!
	*	\brief		Sets the current rotation of the MazeEntity.
	*	\param[in]	rot The desired new orientation as a quaternion
	*	\param[in]  checkForCollisions Set this to false should you not wish
	*				to check for collisions and force the MazeEntity to assume
	*				a rotation.
	*/
	virtual bool setCurrentRotation(glm::quat& rot, bool checkForCollisions = true);

	/*!
	*	\brief		Gets the current maze cell of the MazeEntity.
	*	\return		Pointer to maze cell. Will be NULL if MazeEntity is in
	*				no known maze cell.
	*/
	MazeCell::SPtr getCurrentMazeCell();

	/*!
	*	\brief	Get the maze that this MazeEntity is currently in.
	*	\return	A pointer to the maze this MazeEntity is in. If not in any
	*			the this will return NULL.
	*/
	Maze::SPtr getMazeIn() const;

	/*!
	*	\brief	Sets the max velocity this MazeEntity moves around the maze.
	*	\param[in]	vel The max velocity this MazeEntity should move around the maze.
	*/
	virtual void setVelocity(const glm::vec3& vel);

	/*!
	*	\brief	Gets the max velocity this MazeEntity can move around the maze.
	*	\return	The max velocity this MazeEntity can move around the maze.
	*/
	glm::vec3 getCurrentVelocity();

	/*!
	*	\brief	Gets the max speed this MazeEntity moves around the maze.
	*	\return	The max speed this MazeEntity moves around the maze.
	*/
	float getSpeed();

	/*!
	*	\brief	Sets whether this entity can collide with the walls.
	*	\param[in] collidable True if this entity cannot go through walls or
	*						  false if you do not wish to perform collision detection
	*						  with walls.
	*/
	void setCollidableWithWalls(bool collidable);

	/*!
	*	\brief	Sets whether this entity can collide with other entites.
	*	\param[in] collidable True if this entity can collide with other entities
	*						  false if you do not wish to perform collision detection
	*						  with other entities.
	*/
	void setCollidableWithEntites(bool collidable);

	/*!
	*	\brief	Sets whether this entity can go into start and end maze cells.
	*	\param[in] allowed	True if this entity is allowed into start and end
	*						maze cells. False otherwise.
	*/
	void setAllowedInStartEndCells(bool allowed);

	/*!
	* \see IVisualEntityComponent
	*/
	virtual void update(DE::IVisualEngine::SPtr visualEngine, float dtSecs) {};

	/*!
	* \see IVisualEntityComponent
	*/
	virtual void render(DE::IVisualEngine::SPtr visualEngine) const {};

private:
	Maze::SPtr			m_maze;					///< Pointer to the maze this MazeEntity is in.	
	MazeCell::SPtr		m_currentCell;			///< The current cell of the maze the MazeEntity is in.
	glm::vec3			m_velocity;				///< The max velocity around the maze the MazeEntity can travel.

	CollisionSystem::SPtr	m_collisionSystem;		///< The collision system to use for this component.
	bool					m_collideWithWalls;		///< True if this entity cannot go through walls!
	bool					m_collideWithEntites;	///< True if this entity should collide with other entites.
	bool					m_allowInStartEndCells;	///< True if this entity is allowed in start and end cells.
};