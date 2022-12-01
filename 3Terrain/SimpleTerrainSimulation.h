#pragma once

#include "../DuxsonEngine/Include/Simulation.h"

class SimpleTerrainSimulation : public DE::Simulation
{
	public:
		SimpleTerrainSimulation();
		virtual ~SimpleTerrainSimulation();

		virtual bool init(DE::IVisualEngine::SPtr visualEngine);
};