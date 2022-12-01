#pragma once

#include "../DuxsonEngine/Include/Simulation.h"

class PointLightSimulation : public DE::Simulation
{
	public:
		PointLightSimulation();
		virtual ~PointLightSimulation();

		virtual bool init(DE::IVisualEngine::SPtr visualEngine);
};