/*!********************************************************************
* File:	Simulation.h
*
* \brief	Class representing the simulation that we want to run.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include "ISimulation.h"

namespace DE
{
	class Simulation : public ISimulation
	{
		public:
			/*!
			*	\brief Constructor for the simulation class
			*/
			Simulation();

			/*!
			*	\brief Destructor for the simulation class
			*/
			virtual ~Simulation();

			/*!
			*	\see ISimulation
			*/
			virtual bool init(IVisualEngine::SPtr visualEngine);

			/*!
			*	\see ISimulation
			*/
			virtual void update(const IInput::SPtr input, float dtSecs);

			/*!
			*	\see ISimulation
			*/
			virtual void processVisuals(IVisualEngine::SPtr visualEngine, float dtSecs);

			//Ensure no copy or assignment
			Simulation(Simulation& simulation) = delete;
			void operator=(Simulation& simulation) = delete;

		protected:
			IEntity::SPtr m_root;
	};
}