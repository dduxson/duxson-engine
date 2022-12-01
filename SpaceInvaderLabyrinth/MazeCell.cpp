#include "MazeCell.h"

MazeCell::MazeCell()
	: m_isEndCell(false)
	, m_isStartCell(false)
{
	for (unsigned int i = 0; i < eNumberOfWalls; ++i)
		m_walls[i] = true;
}

MazeCell::~MazeCell()
{

}

void MazeCell::setWallStatus(WallLocation wallLoc, bool up)
{
	m_walls[wallLoc] = up;
}

bool MazeCell::getWallStatus(WallLocation wallLoc) const
{
	return m_walls[wallLoc];
}

void MazeCell::setAsEndCell(bool endCell)
{
	m_isEndCell = endCell;
}

void MazeCell::setAsStartCell(bool startCell)
{
	m_isStartCell = startCell;
}

bool MazeCell::isEndCell() const
{
	return m_isEndCell;
}

bool MazeCell::isStartCell() const
{
	return m_isStartCell;
}