#include "..\DuxsonEngine\include\SFMLWindow.h"
#include "..\DuxsonEngine\include\SFMLInput.h"
#include "..\DuxsonEngine\include\UpdateVisualEntityVisitor.h"
#include "..\DuxsonEngine\include\RenderVisualEntityVisitor.h"
#include "..\DuxsonEngine\include\VisualEngineUtilities.h"
#include "..\DuxsonEngine\include\VisualEngine.h"
#include "..\DuxsonEngine\include\SimulationEngine.h"
#include "..\DuxsonEngine\include\Simulation.h"
#include "..\DuxsonEngine\include\ISimulation.h"
#include "SimpleCubeSimulation.h"
#include <iostream>

using namespace DE;

int main()
{
	IInput::SPtr input = std::make_shared<SFMLInput>();
	IWindow::SPtr window = std::make_shared<SFMLWindow>(input);
	IUpdateVisualEntityVisitor::SPtr updateVisitor = std::make_shared<UpdateVisualEntityVisitor>();
	IRenderVisualEntityVisitor::SPtr renderVisitor = std::make_shared<RenderVisualEntityVisitor>();
	VisualEngineUtilities utilities(window, input, updateVisitor, renderVisitor);
	
	IVisualEngine::SPtr visual_engine = std::make_shared<VisualEngine>();
	visual_engine->setUtilities(utilities);

	ISimulation::SPtr simulation = std::make_shared<SimpleCubeSimulation>();
	ISimulationEngine::SPtr sim_engine = std::make_shared<SimulationEngine>(visual_engine, simulation);

	sim_engine->start();

	return 0;
}