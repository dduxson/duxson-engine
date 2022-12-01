#pragma once

#include "../DuxsonEngine/Include/Simulation.h"
#include "ThreeDMazeEntityBuilder.h"
#include "MapHUDBuilder.h"
#include "CollisionSystem.h"

class MazeLevel : public DE::Simulation
{
	public:
		MazeLevel();
		virtual ~MazeLevel();

		virtual bool init(DE::IVisualEngine::SPtr visualEngine);

		/*!
		*	\brief		Creates a level for the maze game with thea
		*				given number.
		*	\param[in]	levelNum The number of the level to generate (1 based)
		*	\param[in]  visualEngine The visual engine that will be used to show the level.
		*	\remark		Level 1 = 2x2 maze, level2 = 3x3 maze etc. And
		*				level 0 is not exsistent.
		*/
		void createLevel(unsigned int levelNum, DE::IVisualEngine::SPtr visualEngine);

	private:
		Maze::SPtr				m_maze;				///< The actual current maze.
		CollisionSystem::SPtr	m_collisionSystem;	///< The collision system.
		ThreeDMazeEntityBuilder m_threeDGen;		///< The 3d maze entity builder.
		MapHUDBuilder			m_mapHudBuilder;	///< The map hud builder.

};