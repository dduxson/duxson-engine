#include <cstdlib>

#include "Maze.h"
#include "DisjointSets.h"

Maze::Maze()
	: m_numOfRows(2)
	, m_numOfCols(2)
	, m_mazeCellLength(4.0f)
	, m_wallThickness(0.5f)
	, m_wallHeight(4.0f)
{

}

Maze::~Maze()
{

}

void Maze::setMazeCellLength(float length)
{
	if (length > 0.0f)
		m_mazeCellLength = length;
}

void Maze::setMazeWallParams(float thickness, float height)
{
	if (thickness > 0.0f)
		m_wallThickness = thickness;

	if (height > 0.0f)
		m_wallHeight = height;
}

float Maze::getMazeCellLength() const
{
	return m_mazeCellLength;
}

float Maze::getMazeWallHeight() const
{
	return m_wallHeight;
}

float Maze::getMazeWallThickness() const
{
	return m_wallThickness;
}

float Maze::getTotalCellLength() const
{
	return m_mazeCellLength + m_wallThickness;
}

void Maze::setSize(const unsigned int numOfRows, const unsigned int numOfCols)
{
	if (numOfRows < 2 && numOfCols < 2)
		return;

	m_numOfRows = numOfRows;
	m_numOfCols = numOfCols;

	m_cells.clear();
}

unsigned int Maze::getNumOfCols() const
{
	return m_numOfCols;
}

unsigned int Maze::getNumOfRows() const
{
	return m_numOfRows;
}

MazeCell::SPtr Maze::getMazeCell(unsigned int row, unsigned int col) const
{
	if ((!isMazeGenerated()) || row >= m_numOfRows || col >= m_numOfCols)
		return std::shared_ptr<MazeCell>();

	return m_cells[col + (row * m_numOfCols)];
}

bool Maze::isMazeGenerated() const
{
	return m_cells.size() > 0;
}

bool Maze::getStartOrEndCellLoc(unsigned int &row, unsigned int &col, bool start) const
{
	if (!isMazeGenerated())
		return false;

	for (unsigned int rowI = 0; rowI < m_numOfRows; ++rowI)
	{
		for (unsigned int colI = 0; colI < m_numOfCols; ++colI)
		{
			MazeCell::SPtr cell = getMazeCell(rowI, colI);
			if (cell && (((!start) && cell->isEndCell()) || ((start) && cell->isStartCell())))
			{
				row = rowI;
				col = colI;
				return true;
			}
		}
	}

	return false;
}

bool Maze::generateMaze()
{
	unsigned int mazeSize = m_numOfRows * m_numOfCols;
	m_cells.clear();

	for(unsigned int i = 0; i < mazeSize; ++i)
		m_cells.push_back(std::make_shared<MazeCell>());

	DisjointSets diSets = DisjointSets(mazeSize);

	//Generate list of all the walls that can be modified.
	std::list<Wall> walls = getInnerWalls();
	std::list<Wall>::iterator itWall;

	unsigned int wallIndex = 0;
	unsigned int cellIndex1 = 0;
	unsigned int cellIndex2 = 0;

	//While all cells not accessible from any cell.
	while (diSets.getSize() > 1)
	{
		//Find random wall between 2 cells.
		wallIndex = rand() % walls.size();
		itWall = walls.begin();
		advance(itWall, wallIndex);

		cellIndex1 = itWall->cellIndex;
		if (itWall->direction == MazeCell::eWallLocationTop)
			cellIndex2 = cellIndex1 + m_numOfCols;
		else
			cellIndex2 = cellIndex1 - 1;

		//If walls don't belong to same set - we can remove wall.
		if (diSets.find(cellIndex1) != diSets.find(cellIndex2))
		{
			if (itWall->direction == MazeCell::eWallLocationTop && itWall->cellIndex < m_cells.size())
			{
				m_cells[cellIndex1]->setWallStatus(MazeCell::eWallLocationTop, false);
				m_cells[cellIndex2]->setWallStatus(MazeCell::eWallLocationBottom, false);
			}
			else
			{
				m_cells[cellIndex1]->setWallStatus(MazeCell::eWallLocationLeft, false);
				m_cells[cellIndex2]->setWallStatus(MazeCell::eWallLocationRight, false);
			}
			diSets.performUnion(cellIndex1, cellIndex2);
		}

		walls.erase(itWall);
	}

	//Set top right hand corner of maze as the end cell
	if (m_cells.size() > 0)
	{
		m_cells[m_cells.size() - 1]->setAsEndCell(true);
		m_cells[0]->setAsStartCell(true);
	}

	return true;
}

std::list<Maze::Wall> Maze::getInnerWalls()
{
	//Top and left walls needed only.
	std::list<Wall> walls;
	for (unsigned int row = 0; row < m_numOfRows; ++row)
	{
		for (unsigned int col = 0; col < m_numOfCols; ++col)
		{
			//Add top walls if not top row.
			if (row < m_numOfRows - 1)
			{
				Wall wall(row * m_numOfCols + col, MazeCell::eWallLocationTop);
				walls.push_back(wall);
			}

			//Add left walls if not left most wall
			if (col > 0)
			{
				Wall wall(row * m_numOfCols + col, MazeCell::eWallLocationLeft);
				walls.push_back(wall);
			}
		}
	}

	return walls;
}