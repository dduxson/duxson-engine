#include "./Include/SimulationEngine.h"
#include <SFML/Window.hpp>
#include "./Include/Logger.h"

namespace DE
{
	SimulationEngine::SimulationEngine(IVisualEngine::SPtr visualEngine, ISimulation::SPtr simulation)
		: m_visualEngine(visualEngine)
		, m_isRunning(false)
		, m_simulation(simulation)
	{
		if (m_simulation != nullptr && m_visualEngine != nullptr)
			m_simulation->init(visualEngine);
	}

	SimulationEngine::~SimulationEngine()
	{

	}

	void SimulationEngine::start()
	{
		if (m_isRunning)
			return;

		if (m_visualEngine != nullptr && m_simulation != nullptr && m_visualEngine->getUtilities().getWindow() != nullptr)
		{
			Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Starting Simulation Engine");
			run();
		}
		else
		{
			Logger::Instance()->writeToLogFile(Logger::eLogError, "Faile to start Simulation Engine and one or more required pointers is NULL.");
		}
	}

	void SimulationEngine::stop()
	{
		if (!m_isRunning)
			return;

		Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Stopping Simulation Engine");
		m_isRunning = false;
	}

	void SimulationEngine::run()
	{
		m_isRunning = true;

		sf::Clock clock;
		float lastSimTime = 0.0f;
		IWindow::SPtr window = m_visualEngine->getUtilities().getWindow();
		IInput::SPtr input = m_visualEngine->getUtilities().getInput();

		while (m_isRunning)
		{
			float currentSimTime = clock.getElapsedTime().asSeconds();
			float dtSecs = clock.getElapsedTime().asSeconds() - lastSimTime;

			//Update and process inputs
			window->update();
			m_simulation->update(input, dtSecs);

			//TODO: A Visual thread should do this.
			m_simulation->processVisuals(m_visualEngine, dtSecs);
			window->swapBuffers();

			lastSimTime = currentSimTime;

			//Closing of window via a key press
			if (input->isKeyPressed(sf::Keyboard::Escape))
				window->closeWindow();
			
			if (!window->isOpen())
				stop();
		}
	}
}