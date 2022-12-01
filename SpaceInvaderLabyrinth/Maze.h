#pragma once
/*!********************************************************************
* File:	Maze.h
*
* \brief	Class that represents a maze.
* \details  You will need to set the
*			number of rows and columns and then call generateMaze.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include <vector>
#include <list>
#include "MazeCell.h"

class Maze
{
public:
	/*!
	*	\brief	Structure representing a wall. Used for efficient maze
	*			generation.
	*/
	struct Wall
	{
		unsigned int 			cellIndex;
		MazeCell::WallLocation direction;

		Wall()
		{
			cellIndex = 0;
			direction = MazeCell::eWallLocationTop;
		}

		Wall(unsigned int _cellIndex, MazeCell::WallLocation _direction)
		{
			cellIndex = _cellIndex;
			direction = _direction;
		}
	};

public:

	typedef std::shared_ptr<Maze> SPtr;

	/*!
	*	\brief	Constructor for Maze class.
	*/
	Maze();

	/*!
	*	\brief	Destructor for Maze class.
	*/
	virtual ~Maze();

	/*!
	*	\brief	Sets the size of the maze.
	*	\param[in]	numOfRows The integer number of rows you require.
	*	\param[in]	numOfCols The integer number of columns you require.
	*	\remark	This will set the maze generated flag to false.
	*/
	void setSize(const unsigned int numOfRows, const unsigned int numOfCols);

	/*!
	*	\brief	Returns the number of columns.
	*	\return The number of columns this maze is set to.
	*/
	unsigned int getNumOfCols() const;

	/*!
	*	\brief	Returns the number of rows.
	*	\return The number of rows this maze is set to.
	*/
	unsigned int getNumOfRows() const;

	/*!
	*	\brief	Returns a pointer to the maze cell of the given index.
	*	\param[in] row The row of the cell you want. (0 based index)
	*	\param[in] col THe column of the cell you want. (0 based index)
	*	\return Pointer to the maze cell at the given index. If the index
	*			is invalid, this will return NULL.
	*/
	MazeCell::SPtr getMazeCell(unsigned int row, unsigned int col) const;

	/*!
	*	\brief	Generates a maze with the set number of rows and columns
	*	\return True if the maze was sucessfully generated.
	*/
	bool generateMaze();

	/*!
	*	\brief	Returns whether a maze with the current set rows and columns
	*			has been generated.
	*	\return True if the maze was sucessfully generated.
	*/
	bool isMazeGenerated() const;

	/*!
	*	\brief	Makes the unsigned ints given the row and col of
	*			the start or end cell.
	*	\param[in] row Will become the row of the start/end cell.
	*	\param[in] col Will become the col of the start/end cell.
	*	\param[in] start Set this to true if you want the start cell or false
	*					 if you want the end cell.
	*	\return True if we sucessfully found a maze start/end.
	*	\remark	If more than one start/end cell, this will return the first
	*			found.
	*/
	bool getStartOrEndCellLoc(unsigned int &row, unsigned int &col, bool start) const;

	/*!
	*	\brief	Gets the length of a maze cell.
	*	\return The length of a maze cell.
	*	\remark A maze cell is considered to be a square.
	*/
	float getMazeCellLength() const;

	/*!
	*	\brief	Gets the total cell length (i.e. cell length + wall thickness)
	*	\return The total cell length
	*/
	float getTotalCellLength() const;

	/*!
	*	\brief	Gets the thickness of a maze wall.
	*	\return The thickness of a maze wall.
	*/
	float getMazeWallThickness() const;

	/*!
	*	\brief	Gets the height of a maze wall.
	*	\return The height of a maze wall.
	*/
	float getMazeWallHeight() const;

	/*!
	*	\brief	Sets the length of a maze cell.
	*	\param[in] length The length of that a maze cell should be.
	*	\remark A maze cell is considered to be a square.
	*/
	void setMazeCellLength(float length);

	/*!
	*	\brief	Sets the walls height and thickness and number of quads.
	*	\param[in] thickness					The thickness that the maze walls should be.
	*	\param[in] height						The height that the maze walls should be.
	*/
	void setMazeWallParams(float thickness, float height);

private:
	/*!
	*	\brief	Gets all the inner walls (i.e non perimeter) regardless of
	*			whether they are up or down.
	*	\return List contatining all the inner walls.
	*/
	std::list<Wall> getInnerWalls();

private:
	unsigned int				m_numOfRows;		///< The number of rows in the maze.
	unsigned int				m_numOfCols;		///< The number of columns in the maze.
	std::vector<MazeCell::SPtr>	m_cells;			///< The cells in the maze.

	float						m_mazeCellLength;	///< The length that each maze cell should be witout walls. (A cell is assumed a square).
	float						m_wallThickness;	///< The thickness of maze walls.
	float						m_wallHeight;		///< The height of walls in the maze.
};