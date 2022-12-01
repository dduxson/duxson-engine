#pragma once

#include "../DuxsonEngine/Include/Simulation.h"

class SimpleCubeSimulation : public DE::Simulation
{
	public:
		SimpleCubeSimulation();
		virtual ~SimpleCubeSimulation();

		virtual bool init(DE::IVisualEngine::SPtr visualEngine);

	private:
		std::vector<glm::vec4> generateCubeColours();
};