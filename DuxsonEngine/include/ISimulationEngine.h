/*!********************************************************************
* File:	ISimulationEngine.h
*
* \brief	Interface representing the simulation engine that
*			coordinates all processes for a simulation.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

namespace DE
{
	class ISimulationEngine
	{
		public:
			typedef std::shared_ptr<ISimulationEngine> SPtr;

			ISimulationEngine() {}
			virtual ~ISimulationEngine() {}

			virtual void start() = 0;
			virtual void stop() = 0;
	};
}