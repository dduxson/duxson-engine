#pragma once
/*!********************************************************************
*	File:	MazeCell.h
*
* \brief	Class that represents a cell in a maze that has 4 walls.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include <memory>

class MazeCell
{
public:
	typedef std::shared_ptr<MazeCell> SPtr;

	/*!
	*	\brief	Enum for representing where a wall is on a cell.
	*/
	enum WallLocation
	{
		eWallLocationTop,
		eWallLocationBottom,
		eWallLocationLeft,
		eWallLocationRight,

		eNumberOfWalls
	};

public:
	/*!
	*	\brief	Constructor for Maze cell class.
	*	\remark	By default all the walls start up and is not an
	*			end cell.
	*/
	MazeCell();

	/*!
	*	\brief	Destructor for Maze cell class.
	*/
	virtual ~MazeCell();

	/*!
	*	\brief		Sets whether the wall at the given location is up or down.
	*	\param[in]	wallLoc The location of the wall you wish to modify.
	*	\param[in]	up Set to true if you want the wall up, false if you want it down.
	*/
	void setWallStatus(WallLocation wallLoc, bool up);

	/*!
	*	\brief		Gets whether the wall at the given location is up or down.
	*	\param[in]	wallLoc The location of the wall you wish to check.
	*	\return		True if the wall is up, false otherwise.
	*/
	bool getWallStatus(WallLocation wallLoc) const;

	/*!
	*	\brief		Sets whether this cell is an end cell in the maze.
	*	\param[in]	endCell Make this true if this cell should be an end cell, make
	*						false otherwise.
	*	\remark This will also cause this to not be an start cell.
	*/
	void setAsEndCell(bool endCell);

	/*!
	*	\brief		Sets whether this cell is an start cell in the maze.
	*	\param[in]	endCell Make this true if this cell should be an start cell, make
	*						false otherwise.
	*	\remark This will also cause this to not be an end cell.
	*/
	void setAsStartCell(bool startCell);

	/*!
	*	\brief		Gets whether this cell represents an end cell in the maze.
	*	\return		True if the cell is an maze end cell, false otherwise.
	*/
	bool isEndCell() const;

	/*!
	*	\brief		Gets whether this cell represents an start cell in the maze.
	*	\return		True if the cell is an maze start cell, false otherwise.
	*/
	bool isStartCell() const;

private:
	bool m_walls[eNumberOfWalls];	///< The status of the walls of this cell.
	bool m_isEndCell;				///< Whether this cell represents an end cell in the maze.
	bool m_isStartCell;				///< Whether this cell represents a start cell in the maze.
};