#pragma once
/*!********************************************************************
* File:	TwoDMazeNodeBuilder.h
*
* \brief	This class takes a maze object and generates a 2d maze
*			that can be rendered using DuxsonEngine.
* \details It generates vertices from between 0 and 1.
*			Note coordinate system x = left->right and y = bottom->top.
*			Note also that the maze size parameters in the maze object
*			are not used by this builder.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include "IMazeEntityBuilder.h"

class TwoDMazeEntityBuilder : public IMazeEntityBuilder
{
	public:
		/*!
		*	\brief	Constructor for TwoDMazeEntityBuilder class.
		*/
		TwoDMazeEntityBuilder();

		/*!
		*	\brief	Destructor for TwoDMazeEntityBuilder class.
		*/
		virtual ~TwoDMazeEntityBuilder();

		/*!
		*	\brief		Sets the width that the generated maze should be.
		*	\param[in]	width The width that the generated maze should be.
		*/
		void setWidth(float width);

		/*!
		*	\brief		Sets the height that the generated maze should be.
		*	\param[in]	width The height that the generated maze should be.
		*/
		void setHeight(float height);

		/*!
		*	\brief		Sets the parameters for the lines that represent the
		*				maze walls.
		*	\param[in]	width	The width the lines that represent the maze wall
		*						should be.
		*	\param[in]	col		The colour the lines that represent the maze wall
		*						should be.
		*/
		void setWallLineParams(float width, const glm::vec4& col);

		/*!
		*	\brief	see IMazeEntityBuilder
		*/
		virtual DE::Entity::SPtr generateEntity(const Maze &maze);

	private:
		float m_width;		///<The width that the generated maze should be.
		float m_height;		///<The height that the generated maze should be.

		float		m_lineWidth;	///<The width the lines that represent the maze wall should be.
		glm::vec4	m_lineColour;	///<The colour the lines that represent the maze wall should be.
};