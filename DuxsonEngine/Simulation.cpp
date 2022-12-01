#include "./Include/Simulation.h"
#include "./include/Logger.h"

namespace DE
{
	Simulation::Simulation()
	{

	}

	Simulation::~Simulation()
	{
		Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Destroying Simulation");
	}

	bool Simulation::init(IVisualEngine::SPtr visualEngine)
	{
		return true;
	}

	void Simulation::update(const IInput::SPtr input, float dtSecs)
	{

	}

	void Simulation::processVisuals(IVisualEngine::SPtr visualEngine, float dtSecs)
	{
		if (visualEngine && m_root != nullptr)
		{
			visualEngine->update(m_root, dtSecs);
			visualEngine->render(m_root);
		}
	}
}