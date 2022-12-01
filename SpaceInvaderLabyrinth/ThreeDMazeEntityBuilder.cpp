#include "ThreeDMazeEntityBuilder.h"
#include "../DuxsonEngine/Include/ModelVisualEntityComponent.h"
#include "../DuxsonEngine/include/Material.h"
#include "../DuxsonEngine/include/Mesh.h"
#include "../DuxsonEngine/include/ShaderProgram.h"

ThreeDMazeEntityBuilder::ThreeDMazeEntityBuilder()
	: IMazeEntityBuilder()
	, m_numOfFloorQuadsAlongLength(4)
	, m_numOfWallQuadsAlongLength(4)
	//, m_Teleporter(true)
{

}

ThreeDMazeEntityBuilder::~ThreeDMazeEntityBuilder()
{

}

void ThreeDMazeEntityBuilder::setFloorTextureFile(const std::string &fileName)
{
	m_floorTexFileName = fileName;
}

void ThreeDMazeEntityBuilder::setWallTextureFile(const std::string &fileName)
{
	m_wallTexFileName = fileName;
}

/*void ThreeDMazeEntityBuilder::setParticleTextureFile(std::string &fileName)
{
m_particleTexFileName = fileName;
}

void ThreeDMazeEntityBuilder::setTelporter(bool teleporter)
{
m_Teleporter = teleporter;
}*/

void ThreeDMazeEntityBuilder::setNumOfWallQuadsAlongLength(unsigned int num)
{
	if (num > 0)
		m_numOfWallQuadsAlongLength = num;
}

void ThreeDMazeEntityBuilder::setNumOfFloorQuadsAlongLength(unsigned int num)
{
	if (num > 0)
		m_numOfFloorQuadsAlongLength = num;
}

unsigned int ThreeDMazeEntityBuilder::getNumOfWallQuadsAlongLength()
{
	return m_numOfWallQuadsAlongLength;
}

unsigned int ThreeDMazeEntityBuilder::getNumOfFloorQuadsAlongLength()
{
	return m_numOfFloorQuadsAlongLength;
}

DE::Entity::SPtr ThreeDMazeEntityBuilder::generateEntity(const Maze &maze)
{
	DE::Entity::SPtr mazeEntity = std::make_shared<DE::Entity>(true, glm::vec3(0, 0, 0), glm::angleAxis(glm::radians(-90.0f), glm::vec3(1, 0, 0)));

	//We seperate the floor from the walls so we can easily lower the walls if required.
	DE::Geometry::SPtr floor = generateFloor(maze);
	DE::Geometry::SPtr topWalls = generateTopWalls(maze);
	DE::Geometry::SPtr leftWalls = generateLeftWalls(maze);

	//Create meshes and materials.
	DE::Material::SPtr floorMat = std::make_shared<DE::Material>(DE::TextureParams(m_floorTexFileName));
	DE::Material::SPtr wallMat = std::make_shared<DE::Material>(DE::TextureParams(m_wallTexFileName));
	DE::Mesh::SPtr floorMesh = std::make_shared<DE::Mesh>("MazeFloor", floor);
	DE::Mesh::SPtr topWallsMesh = std::make_shared<DE::Mesh>("MazeTopWalls", topWalls);
	DE::Mesh::SPtr leftWallsMesh = std::make_shared<DE::Mesh>("MazeLeftWalls", leftWalls);

	//Create full maze model
	std::map<DE::IMesh::WPtr, DE::IMaterial::WPtr, std::owner_less<DE::IMesh::WPtr> > meshToMaterial;
	meshToMaterial[floorMesh] = floorMat;
	meshToMaterial[topWallsMesh] = wallMat;
	meshToMaterial[leftWallsMesh] = wallMat;

	mazeEntity->addComponent(std::make_shared<DE::ModelVisualEntityComponent>(std::make_shared<DE::Model>(meshToMaterial),
																		 std::make_shared<DE::ShaderProgram>("./Data/Shaders/oneDirLightAndTex.prog")));

	/*unsigned int endRow, endCol, startRow, startCol;
	if( m_Teleporter && maze.getStartOrEndCellLoc( endRow, endCol, false ) &&
	maze.getStartOrEndCellLoc( startRow, startCol, true ))
	{
	addParticleSystems( maze, mazeGroup, startRow, startCol, endRow, endCol );
	}*/

	return mazeEntity;
}

DE::Geometry::SPtr ThreeDMazeEntityBuilder::generateFloor(const Maze &maze)
{
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> norms;
	std::vector<unsigned int> indicies;

	//Generate floor
	float totalCellLength = maze.getTotalCellLength();
	for (unsigned int col = 0; col < maze.getNumOfCols(); col++)
	{
		for (unsigned int row = 0; row < maze.getNumOfRows(); row++)
		{
			glm::vec3 topLeft = glm::vec3(col * totalCellLength, row*totalCellLength, 0.0f);
			generateFloorTriSubMesh(maze, topLeft, verts, norms, uvs, indicies);
		}
	}

	return std::make_shared<DE::Geometry>(indicies, verts, uvs, norms);
}

DE::Geometry::SPtr ThreeDMazeEntityBuilder::generateLeftWalls(const Maze &maze)
{
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> norms;
	std::vector<unsigned int> indicies;

	float totalCellLength = maze.getTotalCellLength();
	float halfWallThickness = maze.getMazeWallThickness() * 0.5f;

	//Generate Left walls
	for (unsigned int col = 0; col < maze.getNumOfCols(); col++)
	{
		for (unsigned int row = 0; row < maze.getNumOfRows(); row++)
		{
			MazeCell::SPtr cell = maze.getMazeCell(row, col);
			MazeCell::SPtr cellToLeft = maze.getMazeCell(row, col - 1);
			MazeCell::SPtr cellAbove = maze.getMazeCell(row + 1, col);

			if (cell == nullptr)
				continue;

			//Always put up the left walls.
			if (cell->getWallStatus(MazeCell::eWallLocationLeft))
			{
				//Make sure walls don't overlap others.
				glm::vec3 startLoc;
				if (cell->getWallStatus(MazeCell::eWallLocationBottom) || (cellToLeft && cellToLeft->getWallStatus(MazeCell::eWallLocationBottom)))
				{
					startLoc = glm::vec3(col * totalCellLength, (row * totalCellLength) + halfWallThickness, 0.0f);
				}
				else
				{
					startLoc = glm::vec3(col * totalCellLength, (row * totalCellLength) - halfWallThickness, 0.0f);
				}
				
				glm::vec3 endLoc;
				if (cell->getWallStatus(MazeCell::eWallLocationTop) || (cellToLeft && cellToLeft->getWallStatus(MazeCell::eWallLocationTop)) ||
					(cellAbove && cellAbove->getWallStatus(MazeCell::eWallLocationLeft)))
				{
					endLoc = glm::vec3(col * totalCellLength, ((row + 1) * totalCellLength) - halfWallThickness, 0.0f);
				}
				else
				{
					endLoc = glm::vec3(col * totalCellLength, ((row + 1) * totalCellLength) + halfWallThickness, 0.0f);
				}

				generateLeftWallSubMesh(maze, startLoc, endLoc, verts, norms, uvs, indicies);
			}

			//Put up right walls around perimeter only. Reason is that the right wall will be in the exact same place as the left otherwise.
			if ((col == maze.getNumOfCols() - 1) && cell->getWallStatus(MazeCell::eWallLocationRight))
			{
				//Make sure walls don't overlap others.
				glm::vec3 startLoc;
				if (cell->getWallStatus(MazeCell::eWallLocationBottom))
				{
					startLoc = glm::vec3((col + 1) * totalCellLength, (row * totalCellLength) + halfWallThickness, 0.0f);
				}
				else
				{
					startLoc = glm::vec3((col + 1) * totalCellLength, (row * totalCellLength) - halfWallThickness, 0.0f);
				}
				glm::vec3 endLoc = glm::vec3((col + 1) * totalCellLength, ((row + 1) * totalCellLength) - halfWallThickness, 0.0f);

				generateLeftWallSubMesh(maze, startLoc, endLoc, verts, norms, uvs, indicies);
			}
		}
	}

	return std::make_shared<DE::Geometry>(indicies, verts, uvs, norms);
}

DE::Geometry::SPtr ThreeDMazeEntityBuilder::generateTopWalls(const Maze &maze)
{
	std::vector<glm::vec3> verts;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> norms;
	std::vector<unsigned int> indicies;

	float totalCellLength = maze.getTotalCellLength();
	float halfWallThickness = maze.getMazeWallThickness() * 0.5f;

	//Generate Top walls
	for (unsigned int col = 0; col < maze.getNumOfCols(); col++)
	{
		for (unsigned int row = 0; row < maze.getNumOfRows(); row++)
		{
			MazeCell::SPtr cell = maze.getMazeCell(row, col);
			MazeCell::SPtr cellToLeft = maze.getMazeCell(row, col - 1);

			if (cell == NULL)
				continue;

			//Always put up the top walls.
			if (cell->getWallStatus(MazeCell::eWallLocationTop))
			{
				//Make sure walls don't overlap others.
				glm::vec3 startLoc;
				if (cellToLeft && cellToLeft->getWallStatus(MazeCell::eWallLocationTop))
				{
					startLoc = glm::vec3((col * totalCellLength) + halfWallThickness, (row + 1) * totalCellLength, 0.0f);
				}
				else
				{
					startLoc = glm::vec3((col * totalCellLength) - halfWallThickness, (row + 1) * totalCellLength, 0.0f);
				}
				glm::vec3 endLoc = glm::vec3(((col + 1) * totalCellLength) + halfWallThickness, (row + 1) * totalCellLength, 0.0f);

				generateTopWallTriSubMesh(maze, startLoc, endLoc, verts, norms, uvs, indicies);
			}

			//Put up down walls around perimeter only. Reason is that the down wall will be in the exact same place as the up otherwise.
			if ((row == 0) && cell->getWallStatus(MazeCell::eWallLocationBottom))
			{
				//Make sure walls don't overlap others.
				glm::vec3 startLoc;
				if (cellToLeft && cellToLeft->getWallStatus(MazeCell::eWallLocationBottom))
				{
					startLoc = glm::vec3((col * totalCellLength) + halfWallThickness, (row)* totalCellLength, 0.0f);
				}
				else
				{
					startLoc = glm::vec3((col * totalCellLength) - halfWallThickness, (row)* totalCellLength, 0.0f);
				}
				glm::vec3 endLoc = glm::vec3(((col + 1) * totalCellLength) + halfWallThickness, (row)* totalCellLength, 0.0f);

				generateTopWallTriSubMesh(maze, startLoc, endLoc, verts, norms, uvs, indicies);
			}
		}
	}

	return std::make_shared<DE::Geometry>(indicies, verts, uvs, norms);
}

void ThreeDMazeEntityBuilder::generateFloorTriSubMesh(const Maze& maze, glm::vec3& topLeft, std::vector<glm::vec3>& verts, std::vector<glm::vec3>& norms, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indicies)
{
	float totalCellLength = maze.getTotalCellLength();
	float lengthPerQuadInCell = totalCellLength / float(m_numOfFloorQuadsAlongLength);
	float reciprocalLengthPerQuadInCell = 1.0f / float(m_numOfFloorQuadsAlongLength);

	//Get what number the verts we are about to add will be in the verts array.
	unsigned int startVertIndex = verts.size();

	//Generate verts for this cell's floor at the given resolution.
	for (unsigned int x = 0; x <= m_numOfFloorQuadsAlongLength; x++)
	{
		for (unsigned int y = 0; y <= m_numOfFloorQuadsAlongLength; y++)
		{
			verts.push_back(glm::vec3(topLeft.x + (x * lengthPerQuadInCell), topLeft.y + (y * lengthPerQuadInCell), topLeft.z));
			uvs.push_back(glm::vec2((x * reciprocalLengthPerQuadInCell), 1 - (y * reciprocalLengthPerQuadInCell)));
			norms.push_back(glm::vec3(0, 0, 1));
		}
	}

	//Generate indicies to draw this (2 triangles per quad)
	for (unsigned int i = 0; i < m_numOfFloorQuadsAlongLength; i++)
	{
		unsigned int offset = startVertIndex + (m_numOfFloorQuadsAlongLength + 1) * i; //+1 as 1 more vertex than number of quads along the length.
		for (unsigned int j = 0; j < m_numOfFloorQuadsAlongLength; j++)
		{
			indicies.push_back(j + offset);
			indicies.push_back(j + 1 + offset);
			indicies.push_back(j + (m_numOfFloorQuadsAlongLength + 2) + offset);
			indicies.push_back(j + (m_numOfFloorQuadsAlongLength + 2) + offset);
			indicies.push_back(j + (m_numOfFloorQuadsAlongLength + 1) + offset);
			indicies.push_back(j + offset);
		}
	}
}

void ThreeDMazeEntityBuilder::generateTopWallTriSubMesh(const Maze& maze, glm::vec3& startLoc, glm::vec3& endLoc, std::vector<glm::vec3>& verts, std::vector<glm::vec3>& norms, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indicies)
{
	float startToEndLength = (endLoc.x - startLoc.x);
	float lengthPerQuadInCell = startToEndLength / float(m_numOfWallQuadsAlongLength);
	float heightPerQuadInCell = maze.getMazeWallHeight() / float(m_numOfWallQuadsAlongLength);
	float reciprocalLengthPerQuadInCell = 1.0f / float(m_numOfWallQuadsAlongLength);
	float halfWallThickness = maze.getMazeWallThickness() * 0.5f;

	//Calculate what number the verts we are about to add will be in the verts array.
	unsigned int startVert = verts.size();

	//Generate larger sides verts for this cell.
	for (unsigned int x = 0; x <= m_numOfWallQuadsAlongLength; x++)
	{
		for (unsigned int z = 0; z <= m_numOfWallQuadsAlongLength; z++)
		{
			//There are 2 sides of the wall as it has a thickness.
			verts.push_back(glm::vec3(startLoc.x + (x * lengthPerQuadInCell), startLoc.y - halfWallThickness, startLoc.z + (z * heightPerQuadInCell)));
			verts.push_back(glm::vec3(startLoc.x + (x * lengthPerQuadInCell), startLoc.y + halfWallThickness, startLoc.z + (z * heightPerQuadInCell)));
			uvs.push_back(glm::vec2((x * reciprocalLengthPerQuadInCell), 1 - (z * reciprocalLengthPerQuadInCell)));
			uvs.push_back(glm::vec2((x * reciprocalLengthPerQuadInCell), 1 - (z * reciprocalLengthPerQuadInCell)));

			if (z == m_numOfWallQuadsAlongLength)
			{
				norms.push_back(glm::vec3(0.0, -0.5, 0.5));
				norms.push_back(glm::vec3(0.0, 0.5, 0.5));
			}
			else
			{
				norms.push_back(glm::vec3(0.0, -1.0, 0.0));
				norms.push_back(glm::vec3(0.0, 1.0, 0.0));
			}
		}
	}

	//Shorter sides verts
	//Top
	unsigned int indexOfShorterHorizSides = verts.size();
	for (unsigned int x = 0; x <= m_numOfWallQuadsAlongLength; x++)
	{
		verts.push_back(glm::vec3(startLoc.x + (x * lengthPerQuadInCell), startLoc.y - halfWallThickness, startLoc.z + maze.getMazeWallHeight()));
		verts.push_back(glm::vec3(startLoc.x + (x * lengthPerQuadInCell), startLoc.y + halfWallThickness, startLoc.z + maze.getMazeWallHeight()));
		uvs.push_back(glm::vec2((x * reciprocalLengthPerQuadInCell), 0.25));
		uvs.push_back(glm::vec2((x * reciprocalLengthPerQuadInCell), 0.0));
		norms.push_back(glm::vec3(0, 0.5, 0.5));
		norms.push_back(glm::vec3(0, -0.5, 0.5));
	}

	//Vertical sides
	unsigned int indexOfShorterVerticalSides = verts.size();
	for (unsigned int z = 0; z <= m_numOfWallQuadsAlongLength; z++)
	{
		verts.push_back(glm::vec3(startLoc.x, startLoc.y - halfWallThickness, startLoc.z + (z * heightPerQuadInCell)));
		verts.push_back(glm::vec3(startLoc.x, startLoc.y + halfWallThickness, startLoc.z + (z * heightPerQuadInCell)));
		verts.push_back(glm::vec3(startLoc.x + startToEndLength, startLoc.y - halfWallThickness, startLoc.z + (z * heightPerQuadInCell)));
		verts.push_back(glm::vec3(startLoc.x + startToEndLength, startLoc.y + halfWallThickness, startLoc.z + (z * heightPerQuadInCell)));

		if (z == m_numOfWallQuadsAlongLength)
		{
			norms.push_back(glm::vec3(-0.5, 0.0, 0.5));
			norms.push_back(glm::vec3(-0.5, 0.0, 0.5));
			norms.push_back(glm::vec3(0.5, 0.0, 0.5));
			norms.push_back(glm::vec3(0.5, 0.0, 0.5));
		}
		else
		{
			norms.push_back(glm::vec3(-1.0, 0.0, 0.0));
			norms.push_back(glm::vec3(-1.0, 0.0, 0.0));
			norms.push_back(glm::vec3(1.0, 0.0, 0.0));
			norms.push_back(glm::vec3(1.0, 0.0, 0.0));
		}

		uvs.push_back(glm::vec2(0.25, 1 - (z * reciprocalLengthPerQuadInCell)));
		uvs.push_back(glm::vec2(0.0, 1 - (z * reciprocalLengthPerQuadInCell)));
		uvs.push_back(glm::vec2(0.25, 1 - (z * reciprocalLengthPerQuadInCell)));
		uvs.push_back(glm::vec2(0.0, 1 - (z * reciprocalLengthPerQuadInCell)));
	}

	//Generate indicies to draw this.
	unsigned int numOfwalls = 2; //2 as there are 2 walls per cell as wall has thickness.
	for (unsigned int i = 0; i < m_numOfWallQuadsAlongLength; i++)
	{
		int offset = startVert + ((m_numOfWallQuadsAlongLength + 1) * i * numOfwalls);
		for (unsigned int j = 0; j < m_numOfWallQuadsAlongLength * numOfwalls; j++)
		{
			indicies.push_back(j + offset);
			indicies.push_back(j + 2 + offset);
			indicies.push_back(j + ((m_numOfWallQuadsAlongLength + 2)*numOfwalls) + offset);
			indicies.push_back(j + ((m_numOfWallQuadsAlongLength + 2)*numOfwalls) + offset);
			indicies.push_back(j + ((m_numOfWallQuadsAlongLength + 1)*numOfwalls) + offset);
			indicies.push_back(j + offset);
		}
	}

	//Shorter sides indicies.
	for (unsigned int i = 0; i < m_numOfWallQuadsAlongLength; i++)
	{
		unsigned int twoI = i * 2;
		indicies.push_back(indexOfShorterHorizSides + twoI);
		indicies.push_back(indexOfShorterHorizSides + 1 + twoI);
		indicies.push_back(indexOfShorterHorizSides + 2 + twoI);
		indicies.push_back(indexOfShorterHorizSides + 2 + twoI);
		indicies.push_back(indexOfShorterHorizSides + 3 + twoI);
		indicies.push_back(indexOfShorterHorizSides + 1 + twoI);
	}
	for (unsigned int j = 0; j < m_numOfWallQuadsAlongLength * numOfwalls; j++)
	{
		unsigned int twoJ = j * 2;
		indicies.push_back(indexOfShorterVerticalSides + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 1 + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 4 + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 4 + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 5 + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 1 + twoJ);
	}
}

void ThreeDMazeEntityBuilder::generateLeftWallSubMesh(const Maze& maze, glm::vec3& startLoc, glm::vec3& endLoc, std::vector<glm::vec3>& verts, std::vector<glm::vec3>& norms, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indicies)
{
	float startToEndLength = (endLoc.y - startLoc.y);
	float lengthPerQuadInCell = startToEndLength / float(m_numOfWallQuadsAlongLength);
	float heightPerQuadInCell = maze.getMazeWallHeight() / float(m_numOfWallQuadsAlongLength);
	float reciprocalLengthPerQuadInCell = 1.0f / float(m_numOfWallQuadsAlongLength);
	float halfWallThickness = maze.getMazeWallThickness() * 0.5f;

	//Calculate what number the verts we are about to add will be in the verts array.
	unsigned int startVert = verts.size();

	//Generate larger sides verts for this cell.
	for (unsigned int y = 0; y <= m_numOfWallQuadsAlongLength; y++)
	{
		for (unsigned int z = 0; z <= m_numOfWallQuadsAlongLength; z++)
		{
			//There are 2 sides of the wall as it has a thickness.
			verts.push_back(glm::vec3(startLoc.x - halfWallThickness, startLoc.y + (y * lengthPerQuadInCell), startLoc.z + (z * heightPerQuadInCell)));
			verts.push_back(glm::vec3(startLoc.x + halfWallThickness, startLoc.y + (y * lengthPerQuadInCell), startLoc.z + (z * heightPerQuadInCell)));
			uvs.push_back(glm::vec2((y * reciprocalLengthPerQuadInCell), 1 - (z * reciprocalLengthPerQuadInCell)));
			uvs.push_back(glm::vec2((y * reciprocalLengthPerQuadInCell), 1 - (z * reciprocalLengthPerQuadInCell)));

			if (z == m_numOfWallQuadsAlongLength)
			{
				norms.push_back(glm::vec3(-0.5, 0.0, 0.5));
				norms.push_back(glm::vec3(0.5, 0.0, 0.5));
			}
			else
			{
				norms.push_back(glm::vec3(-1.0, 0.0, 0.0));
				norms.push_back(glm::vec3(1.0, 0.0, 0.0));
			}
		}
	}

	//Shorter sides verts
	unsigned int indexOfShorterHorizSides = verts.size();
	for (unsigned int y = 0; y <= m_numOfWallQuadsAlongLength; y++)
	{
		verts.push_back(glm::vec3(startLoc.x - halfWallThickness, startLoc.y + (y * lengthPerQuadInCell), startLoc.z + maze.getMazeWallHeight()));
		verts.push_back(glm::vec3(startLoc.x + halfWallThickness, startLoc.y + (y * lengthPerQuadInCell), startLoc.z + maze.getMazeWallHeight()));
		uvs.push_back(glm::vec2((y * reciprocalLengthPerQuadInCell), 0.25));
		uvs.push_back(glm::vec2((y * reciprocalLengthPerQuadInCell), 0.0));
		norms.push_back(glm::vec3(0.5, 0.0, 0.5));
		norms.push_back(glm::vec3(-0.5, 0.0, 0.5));
	}

	unsigned int indexOfShorterVerticalSides = verts.size();
	for (unsigned int z = 0; z <= m_numOfWallQuadsAlongLength; z++)
	{
		verts.push_back(glm::vec3(startLoc.x - halfWallThickness, startLoc.y, startLoc.z + (z * heightPerQuadInCell)));
		verts.push_back(glm::vec3(startLoc.x + halfWallThickness, startLoc.y, startLoc.z + (z * heightPerQuadInCell)));
		verts.push_back(glm::vec3(startLoc.x - halfWallThickness, startLoc.y + startToEndLength, startLoc.z + (z * heightPerQuadInCell)));
		verts.push_back(glm::vec3(startLoc.x + halfWallThickness, startLoc.y + startToEndLength, startLoc.z + (z * heightPerQuadInCell)));

		if (z == m_numOfWallQuadsAlongLength)
		{
			norms.push_back(glm::vec3(0.0, -0.5, 0.5));
			norms.push_back(glm::vec3(0.0, -0.5, 0.5));
			norms.push_back(glm::vec3(0.0, 0.5, 0.5));
			norms.push_back(glm::vec3(0.0, 0.5, 0.5));
		}
		else
		{
			norms.push_back(glm::vec3(0.0, -1.0, 0.0));
			norms.push_back(glm::vec3(0.0, -1.0, 0.0));
			norms.push_back(glm::vec3(0.0, 1.0, 0.0));
			norms.push_back(glm::vec3(0.0, 1.0, 0.0));
		}

		uvs.push_back(glm::vec2(0.25, 1 - (z * reciprocalLengthPerQuadInCell)));
		uvs.push_back(glm::vec2(0.0, 1 - (z * reciprocalLengthPerQuadInCell)));
		uvs.push_back(glm::vec2(0.25, 1 - (z * reciprocalLengthPerQuadInCell)));
		uvs.push_back(glm::vec2(0.0, 1 - (z * reciprocalLengthPerQuadInCell)));
	}

	//Generate indicies to draw this.
	unsigned int numOfwalls = 2; //2 as there are 2 walls per cell as wall has thickness.
	for (unsigned int i = 0; i < m_numOfWallQuadsAlongLength; i++)
	{
		unsigned int offset = startVert + ((m_numOfWallQuadsAlongLength + 1) * i * numOfwalls);
		for (unsigned int j = 0; j < m_numOfWallQuadsAlongLength * numOfwalls; j++)
		{
			indicies.push_back(j + offset);
			indicies.push_back(j + 2 + offset);
			indicies.push_back(j + ((m_numOfWallQuadsAlongLength + 2)*numOfwalls) + offset);
			indicies.push_back(j + ((m_numOfWallQuadsAlongLength + 2)*numOfwalls) + offset);
			indicies.push_back(j + ((m_numOfWallQuadsAlongLength + 1)*numOfwalls) + offset);
			indicies.push_back(j + offset);
		}
	}

	//Shorter sides indicies.
	for (unsigned int i = 0; i < m_numOfWallQuadsAlongLength; i++)
	{
		unsigned int twoI = i * 2;
		indicies.push_back(indexOfShorterHorizSides + twoI);
		indicies.push_back(indexOfShorterHorizSides + 1 + twoI);
		indicies.push_back(indexOfShorterHorizSides + 2 + twoI);
		indicies.push_back(indexOfShorterHorizSides + 2 + twoI);
		indicies.push_back(indexOfShorterHorizSides + 3 + twoI);
		indicies.push_back(indexOfShorterHorizSides + 1 + twoI);
	}
	for (unsigned int j = 0; j < m_numOfWallQuadsAlongLength * numOfwalls; j++)
	{
		unsigned int twoJ = j * 2;
		indicies.push_back(indexOfShorterVerticalSides + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 1 + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 4 + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 4 + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 5 + twoJ);
		indicies.push_back(indexOfShorterVerticalSides + 1 + twoJ);
	}
}

/*void ThreeDMazeNodeBuilder::addParticleSystems(const Maze& maze, osg::Group* parent, unsigned int startRow, unsigned int startCol, unsigned int endRow, unsigned int endCol)
{
float totalCellLength		= maze.getTotalCellLength();
float halfTotalCellLength	= totalCellLength * 0.5f;

osg::ref_ptr<osg::MatrixTransform> mtEnd = new osg::MatrixTransform;
mtEnd->setMatrix( osg::Matrix::translate(endRow*totalCellLength + halfTotalCellLength, endCol*totalCellLength + halfTotalCellLength, 0.0f) );
osg::ref_ptr<osg::MatrixTransform> mtStart = new osg::MatrixTransform;
mtStart->setMatrix( osg::Matrix::translate(startRow*totalCellLength + halfTotalCellLength, startCol*totalCellLength + halfTotalCellLength, 0.0f) );

osgParticle::ParticleSystem* psEn = createEndParticleSystem( maze, mtEnd.get() );
osgParticle::ParticleSystem* psSt = createStartParticleSystem( maze, mtStart.get() );

osg::ref_ptr<osgParticle::ParticleSystemUpdater> updater = new osgParticle::ParticleSystemUpdater;
updater->addParticleSystem( psEn );
updater->addParticleSystem( psSt );

parent->addChild( updater.get() );
parent->addChild( mtEnd.get() );
parent->addChild( mtStart.get() );
}

osgParticle::ParticleSystem* ThreeDMazeNodeBuilder::createEndParticleSystem(const Maze& maze, osg::Group* parent )
{
float particleSpeed		= 2.0f;
float particleRadius	= 0.05f;

osgParticle::Particle ptemplate;
ptemplate.setLifeTime(maze.getMazeWallHeight() / particleSpeed);
ptemplate.setSizeRange(osgParticle::rangef(0.05f, 0.05f));
ptemplate.setAlphaRange(osgParticle::rangef(0.0f, 1.5f));
ptemplate.setColorRange(osgParticle::rangev4( osg::Vec4(0.0f, 0.0f, 0.5f, 1.5f), osg::Vec4(0, 1.0f, 1.0f, 0.0f)));
ptemplate.setRadius(particleRadius);
ptemplate.setMass(0.05f);

osg::ref_ptr<osgParticle::ParticleSystem> ps = new osgParticle::ParticleSystem;
ps->setDefaultAttributes(m_particleTexFileName, false, false);
ps->setDefaultParticleTemplate(ptemplate);

osg::ref_ptr<osgParticle::RandomRateCounter> rrc = new osgParticle::RandomRateCounter;
rrc->setRateRange( 150, 180 );

osg::ref_ptr<osgParticle::BoxPlacer> placer = new osgParticle::BoxPlacer;
float minRange = -maze.getMazeCellLength()/2.0f + particleRadius;
float maxRange = maze.getMazeCellLength()/2.0f - particleRadius;
placer->setXRange(minRange, maxRange);
placer->setYRange(minRange, maxRange);
placer->setZRange(0, 0);

osg::ref_ptr<osgParticle::RadialShooter> shooter = new osgParticle::RadialShooter;
shooter->setInitialSpeedRange(particleSpeed, particleSpeed);
shooter->setThetaRange(0,0);

osg::ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter;
emitter->setParticleSystem( ps.get() );
emitter->setCounter( rrc.get() );
emitter->setPlacer( placer.get() );
emitter->setShooter( shooter.get() );

osg::ref_ptr<osgParticle::ModularProgram> program = new osgParticle::ModularProgram;
program->setParticleSystem( ps.get() );

osg::ref_ptr<osg::Geode> geode = new osg::Geode;
geode->addDrawable( ps.get() );
parent->addChild( emitter.get() );
parent->addChild( program.get() );
parent->addChild( geode.get() );
return ps.get();
}

osgParticle::ParticleSystem* ThreeDMazeNodeBuilder::createStartParticleSystem(const Maze& maze, osg::Group* parent )
{
float particleSpeed		= 2.0f;
float particleRadius	= 0.05f;

osgParticle::Particle ptemplate;
ptemplate.setLifeTime(maze.getMazeWallHeight() / particleSpeed);
ptemplate.setSizeRange(osgParticle::rangef(0.05f, 0.05f));
ptemplate.setAlphaRange(osgParticle::rangef(0.0f, 1.5f));
ptemplate.setColorRange(osgParticle::rangev4( osg::Vec4(0.0f, 0.5f, 0.0f, 1.5f), osg::Vec4(0, 1.0f, 0.0f, 0.0f)));
ptemplate.setRadius(particleRadius);
ptemplate.setMass(0.05f);

osg::ref_ptr<osgParticle::ParticleSystem> ps = new osgParticle::ParticleSystem;
ps->setDefaultAttributes(m_particleTexFileName, false, false);
ps->setDefaultParticleTemplate(ptemplate);

osg::ref_ptr<osgParticle::RandomRateCounter> rrc = new osgParticle::RandomRateCounter;
rrc->setRateRange( 150, 180 );

osg::ref_ptr<osgParticle::BoxPlacer> placer = new osgParticle::BoxPlacer;
float minRange = -maze.getMazeCellLength()/2.0f + particleRadius;
float maxRange = maze.getMazeCellLength()/2.0f - particleRadius;
placer->setXRange(minRange, maxRange);
placer->setYRange(minRange, maxRange);
placer->setZRange(0, 0);

osg::ref_ptr<osgParticle::RadialShooter> shooter = new osgParticle::RadialShooter;
shooter->setInitialSpeedRange(particleSpeed, particleSpeed);
shooter->setThetaRange(0,0);

osg::ref_ptr<osgParticle::ModularEmitter> emitter = new osgParticle::ModularEmitter;
emitter->setParticleSystem( ps.get() );
emitter->setCounter( rrc.get() );
emitter->setPlacer( placer.get() );
emitter->setShooter( shooter.get() );

osg::ref_ptr<osgParticle::ModularProgram> program = new osgParticle::ModularProgram;
program->setParticleSystem( ps.get() );

osg::ref_ptr<osg::Geode> geode = new osg::Geode;
geode->addDrawable( ps.get() );
parent->addChild( emitter.get() );
parent->addChild( program.get() );
parent->addChild( geode.get() );
return ps.get();
}*/