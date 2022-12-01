#pragma once
/*!********************************************************************
* File:	MapHUDBuilder.h
*
* \brief	Class that generates an maze map HUD that can be rendered
*			with DuxsonEngine.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include "../DuxsonEngine/Include/Entity.h"
#include "HUDBuilder.h"
#include "TwoDMazeEntityBuilder.h"

class MapHUDBuilder : public HUDBuilder
{
public:
	/*!
	*	\brief	Constructor for MapHUDBuilder class.
	*/
	MapHUDBuilder();

	/*!
	*	\brief	Destructor for MapHUDBuilder class.
	*/
	virtual ~MapHUDBuilder();

	/*!
	*	\brief	Sets the entity that will be represented on this map.
	*	\param[in] entity Pointer to the entity that should be represented
	*					  on this map.
	*/
	void setEntity(DE::Entity::SPtr entity);

	/*!
	*	\brief	see IMazeEntityBuilder
	*/
	virtual DE::Entity::SPtr generateEntity(const Maze &maze);

private:
	/*!
	*	\brief	Generates an arrow (triangle) for where the entity
	*			is on the map.
	*	\param[in] length The length the arrow should be.
	*	\param[in] width The width the arrow should be.
	*	\param[in] col A vec4 of the colour the arrow should be.
	*	\return	An DE::Entity of the arrow.
	*/
	DE::Entity::SPtr generateArrowEntity(float length, float width, const glm::vec4 &col);

private:
	TwoDMazeEntityBuilder			m_twoDMazeBuilder;	///< The 2d maze Builder.
	DE::Entity::SPtr				m_entity;			///< Pointer to the entity that should be represented on this map.
};