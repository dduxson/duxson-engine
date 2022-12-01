#pragma once
/*!********************************************************************
* File:	IMazeNodeBuilder.h
*
* \brief	Abstract Builder class that defines the interface for a
*			Maze Node Builder.
* \details This class should be the base class for any classes that
*			generate enities related to the maze. It should take a maze
*			and generate an entity from it which can then be
*			rendered using the DuxsonEngine.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include "../DuxsonEngine/Include/Entity.h"
#include "Maze.h"

class IMazeEntityBuilder
{
	public:
		/*!
		*	\brief	Constructor for IMazeEntityBuilder class.
		*/
		IMazeEntityBuilder() {};

		/*!
		*	\brief	Destructor for IMazeEntityBuilder class.
		*/
		virtual ~IMazeEntityBuilder() {};

		/*!
		*	\brief	Generates a entity from the given maze. This is
		*			the Builder function.
		*	\param[in]	maze The maze you wish to generate an entity for.
		*/
		virtual DE::Entity::SPtr generateEntity(const Maze &maze) = 0;
};