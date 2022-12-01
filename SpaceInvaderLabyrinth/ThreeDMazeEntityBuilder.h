#pragma once
/*!********************************************************************
* File:	ThreeDMazeEntityBuilder.h
*
* \brief	This class takes a maze object and generates a 3d maze
*			that can be rendered using DuxsonEngine.
*
* \author	David Duxson
*
* \date	02/11/2011
*
**********************************************************************/
#include "IMazeEntityBuilder.h"
#include <string>
#include "../DuxsonEngine/Include/Model.h"
//#include <osg/Texture2D>
//#include <osgParticle/ParticleSystem>

class ThreeDMazeEntityBuilder : public IMazeEntityBuilder
{
public:
	/*!
	*	\brief	Constructor for ThreeDMazeEntityBuilder class.
	*/
	ThreeDMazeEntityBuilder();

	/*!
	*	\brief	Destructor for ThreeDMazeEntityBuilder class.
	*/
	virtual ~ThreeDMazeEntityBuilder();

	/*!
	*	\brief	see IMazeEntityBuilder
	*/
	virtual DE::Entity::SPtr generateEntity(const Maze &maze);

	/*!
	*	\brief	Sets the floor texture filename.
	*	\param[in] fileName The full filname of the texture you wish to
	*						use for the floor of the maze.
	*/
	void setFloorTextureFile(const std::string &fileName);

	/*!
	*	\brief	Sets the wall texture filename.
	*	\param[in] fileName The full filname of the texture you wish to
	*						use for the walls of the maze.
	*/
	void setWallTextureFile(const std::string &fileName);

	/*!
	*	\brief	Sets the maze telporter particle texture filename.
	*	\param[in] fileName The full filname of the texture you wish to
	*						use for the particles marking the start/end of the
	*						maze.
	*/
	//void setParticleTextureFile(std::string &fileName);

	/*!
	*	\brief	Sets whether a teleportation effect should be present
	*			at the start/end of the maze.
	*	\param[in] teleporter Set to true if you wish to have a telporter
	*						  placed at the maze start/end.
	*/
	//void setTelporter(bool teleporter);

	/*!
	*	\brief	Sets the number of quads along the length of the wall.
	*	\param[in] num	The number of quads along the length of the wall.
	*	\remark TotalQuads = num * num.
	*/
	void setNumOfWallQuadsAlongLength(unsigned int num);

	/*!
	*	\brief	Sets the number of quads along the length of the floor.
	*	\param[in] num The number of quads along the length of the floor.
	*	\remark TotalQuads = num * num.
	*/
	void setNumOfFloorQuadsAlongLength(unsigned int num);

	/*!
	*	\brief	Gets the number of quads along the length of the wall.
	*	\return The number of quads along the length of the wall.
	*	\remark TotalQuads = num * num.
	*/
	unsigned int getNumOfWallQuadsAlongLength();

	/*!
	*	\brief	Gets the number of quads along the length of the floor.
	*	\return The number of quads along the length of the floor.
	*	\remark TotalQuads = num * num.
	*/
	unsigned int getNumOfFloorQuadsAlongLength();

private:
	/*!
	*	\brief	Generates the Maze's floor
	*	\param[in]	maze The maze you wish to generate an entity for.
	*	\return	The geometry that represents the maze floor.
	*/
	DE::Geometry::SPtr generateFloor(const Maze &maze);

	/*!
	*	\brief	Generates the Maze's left walls
	*	\param[in]	maze The maze you wish to generate an entity for.
	*	\return	The geometry that represents the maze's left walls.
	*/
	DE::Geometry::SPtr generateLeftWalls(const Maze &maze);

	/*!
	*	\brief	Generates the Maze's top walls
	*	\param[in]	maze The maze you wish to generate an entity for.
	*	\return	The geometry that represents the maze's top walls.
	*/
	DE::Geometry::SPtr generateTopWalls(const Maze &maze);

	/*!
	*	\brief	Generates the verts and uvs of the cell's floor.
	*	\param[in] maze			The maze you wish to generate an osg::Node for.
	*	\param[in] topLeft		The top left point of the cell floor.
	*	\param[in] verts		Reference to the array to add vertices to. Will place vertices
	*							after pre-exsiting ones.
	*	\param[in] norms		Reference to the array to add normals to. Will place normals
	*							after pre-exsiting ones.
	*	\param[in] uvs			Reference to the array to add texture coordinates to. Will place uvs
	*							after pre-exsiting ones.
	*	\param[in] indicies		Reference to the array to add indicies to. Will place indicies
	*							after pre-existing ones.
	*/
	void generateFloorTriSubMesh(const Maze& maze, glm::vec3& topLeft, std::vector<glm::vec3>& verts, std::vector<glm::vec3>& norms, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indicies);

	/*!
	*	\brief	Generates the verts norms and uvs of the cell's top walls.
	*	\param[in] maze			The maze you wish to generate an osg::Node for.
	*	\param[in] topLeft		The top left point of the top cell wall.
	*	\param[in] verts		Reference to the array to add vertices to. Will place vertices
	*							after pre-exsiting ones.
	*	\param[in] norms		Reference to the array to add normals to. Will place normals
	*							after pre-exsiting ones.
	*	\param[in] uvs			Reference to the array to add texture coordinates to. Will place uvs
	*							after pre-exsiting ones.
	*	\param[in] indicies		Reference to the array to add indicies to. Will place indicies
	*							after pre-existing ones.
	*/
	void generateTopWallTriSubMesh(const Maze& maze, glm::vec3& startLoc, glm::vec3& endLoc, std::vector<glm::vec3>& verts, std::vector<glm::vec3>& norms, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indicies);

	/*!
	*	\brief	Generates the verts norms and uvs of the cell's left walls.
	*	\param[in] maze			The maze you wish to generate an osg::Node for.
	*	\param[in] topLeft		The top left point of the left cell wall.
	*	\param[in] verts		Reference to the array to add vertices to. Will place vertices
	*							after pre-exsiting ones.
	*	\param[in] norms		Reference to the array to add normals to. Will place normals
	*							after pre-exsiting ones.
	*	\param[in] uvs			Reference to the array to add texture coordinates to. Will place uvs
	*							after pre-exsiting ones.
	*	\param[in] indicies		Reference to the array to add indicies to. Will place indicies
	*							after pre-existing ones.
	*/
	void generateLeftWallSubMesh(const Maze& maze, glm::vec3& startLoc, glm::vec3& endLoc, std::vector<glm::vec3>& verts, std::vector<glm::vec3>& norms, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indicies);

	/*!
	*	\brief		Creates particle systems to mark the entrance and end of the maze.
	*	\param[in]	maze The maze you wish to generate an osg::Node for.
	*	\param[in]	parent  The osg::Group pointer to whom ever should be the parent
	*						of the particle systems should be.
	*	\param[in]  endRow  The end row of the maze.
	*	\param[in]	endCol  The end col of the maze.
	*	\param[in]  startRow  The start row of the maze.
	*	\param[in]	startCol  The start col of the maze.
	*/
	//void addParticleSystems(const Maze& maze, osg::Group* parent, unsigned int startRow, unsigned int startCol, unsigned int endRow, unsigned int endCol);

	/*!
	*	\brief		Creates a particle system to mark the end of the maze.
	*	\param[in]	maze The maze you wish to generate an osg::Node for.
	*	\param[in]	parent  The osg::Group pointer to whom ever should be the parent
	*						of this particle system. This is usually a osg::MatrixTransform
	*						of where the particle system should be placed in the world.
	*	\return		The osgParticle::ParticleSystem.
	*/
	//osgParticle::ParticleSystem* createEndParticleSystem(const Maze& maze, osg::Group* parent );

	/*!
	*	\brief		Creates a particle system to mark the start of the maze.
	*	\param[in]	maze The maze you wish to generate an osg::Node for.
	*	\param[in]	parent  The osg::Group pointer to whom ever should be the parent
	*						of this particle system. This is usually a osg::MatrixTransform
	*						of where the particle system should be placed in the world.
	*	\return		The osgParticle::ParticleSystem.
	*/
	//osgParticle::ParticleSystem* createStartParticleSystem(const Maze& maze, osg::Group* parent );

private:
	std::string		m_floorTexFileName;				///< The filename of the texture that should be used for the floor.
	std::string		m_wallTexFileName;				///< The filename of the texture that should be used for the walls.
													//std::string		m_particleTexFileName;			///< The filename of the texture that should be used for the teleporter maze particles.

	unsigned int	m_numOfFloorQuadsAlongLength;	///< The number of quads there should be along the length of the floor (i.e. total quads = m_numOfFloorQuadsAlongLength * m_numOfFloorQuadsAlongLength)
	unsigned int	m_numOfWallQuadsAlongLength;	///< The number of quads there should be along the length of the wall (i.e. total quads = m_numOfWallQuadsAlongLength * m_numOfWallQuadsAlongLength)

													//bool			m_Teleporter;					///< Whether a particle system (teleporter) marks the start/end of the maze level.
};