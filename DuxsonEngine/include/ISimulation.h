/*!********************************************************************
* File:	ISimulation.h
*
* \brief	Interface representing the simulation that we want to run.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include "IEntity.h"
#include "IVisualEngine.h"
#include "IVisualEntityComponent.h"
#include "IInput.h"
#include "Logger.h"

namespace DE
{
	class ISimulation
	{
		public:
			typedef std::shared_ptr<ISimulation> SPtr;

			ISimulation() {}
			virtual ~ISimulation() {}

			/*!
			*	\brief	Anything required for initialising the simulation should be
			*			done in here.
			*	\param[in] visualEngine The visual engine and guarantees OpenGL
			*							context is already created.
			*	\return True if successful initialisation, false otherwise.
			*/
			virtual bool init(IVisualEngine::SPtr visualEngine) = 0;

			/*!
			*	\brief	Any additional updates that should be done reguarly by the main thread
			*			should be in here.
			*	\param[in] The input devices state.
			*	\param[in] The time since we last called this function.
			*/
			virtual void update(const IInput::SPtr input, float dtSecs) = 0;

			/*!
			*	\brief	Any additional things that should be done reguarly by the visuals thread
			*			should be in here.
			*	\param[in] The current visual engine.
			*	\param[in] The time since we last called this function.
			*/
			virtual void processVisuals(IVisualEngine::SPtr visualEngine, float dtSecs) = 0;
	};
}