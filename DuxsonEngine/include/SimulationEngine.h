/*!********************************************************************
* File:	SimulationEngine.h
*
* \brief	Class representing the simulation engine that
*			coordinates all processes for a simulation.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include "IVisualEngine.h"
#include "ISimulation.h"
#include "ISimulationEngine.h"

namespace DE
{
	class SimulationEngine : public ISimulationEngine
	{
	public:
		SimulationEngine(IVisualEngine::SPtr visualEngine, ISimulation::SPtr simulation);
		~SimulationEngine();

		void start();
		void stop();

	private:
		void run();

	private:
		bool	m_isRunning;

		IVisualEngine::SPtr	m_visualEngine;
		ISimulation::SPtr	m_simulation;
	};
}
