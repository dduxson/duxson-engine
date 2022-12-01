#include "SimpleCubeSimulation.h"
#include "../DuxsonEngine/include/VisualEntityRotatorComponent.h"
#include "../DuxsonEngine/Include/DirectionalLight.h"
#include "../DuxsonEngine/Include/CameraComponent.h"
#include "../DuxsonEngine/Include/KeyboardMoveComponent.h"
#include "../DuxsonEngine/Include/MouseLookComponent.h"
#include "../DuxsonEngine/Include/CubeGeometry.h"
#include "../DuxsonEngine/include/Entity.h"
#include "../DuxsonEngine/include/Model.h"
#include "../DuxsonEngine/include/Mesh.h"
#include "../DuxsonEngine/include/ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

SimpleCubeSimulation::SimpleCubeSimulation()
{

}

SimpleCubeSimulation::~SimpleCubeSimulation()
{
	
}

bool SimpleCubeSimulation::init(DE::IVisualEngine::SPtr visualEngine)
{
	//Setup Scene graph
	m_root = std::make_shared<DE::Entity>();

	//Setup a camera and enable it to move around
	DE::IEntity::SPtr mainCam = std::make_shared<DE::Entity>();
	mainCam->addComponent(std::make_shared<DE::MouseLookComponent>());
	mainCam->addComponent(std::make_shared<DE::KeyboardMoveComponent>());
	mainCam->addComponent(std::make_shared<DE::CameraComponent>(glm::perspective(45.0f, visualEngine->getUtilities().getWindow()->getAspect(), 0.1f, 1000.0f)));
	mainCam->setParent(m_root);

	//Setup a directional light (intial direction is +z so rotate 180 around y axis to point to -z)
	DE::IEntity::SPtr dirLight = std::make_shared<DE::Entity>(true, glm::vec3(0, 0, 0), glm::angleAxis(glm::radians(180.0f), glm::vec3(0, 1, 0)));
	dirLight->addComponent(std::make_shared<DE::DirectionalLight>(1, glm::vec3(1.0, 1.0, 1.0)));
	dirLight->setParent(mainCam);

	//Setup our test cube
	DE::IEntity::SPtr cube = std::make_shared<DE::Entity>(true, glm::vec3(0.0f, 0.0f, -4.00f));
	DE::IModel::SPtr cubeModel = std::make_shared<DE::Model>(std::make_shared<DE::Mesh>("cube", std::make_shared<DE::CubeGeometry>(generateCubeColours())), nullptr);
	cube->addComponent(std::make_shared<DE::VisualEntityRotatorComponent>(cubeModel, std::make_shared<DE::ShaderProgram>("./Data/Shaders/oneDirLightAndColour.prog")));
	cube->setParent(dirLight);

	return true;
}

std::vector<glm::vec4> SimpleCubeSimulation::generateCubeColours()
{
	std::vector<glm::vec4> colours;
	colours.push_back(glm::vec4(0, 0, 1, 1));
	colours.push_back(glm::vec4(1, 0, 1, 1));
	colours.push_back(glm::vec4(1, 1, 1, 1));
	colours.push_back(glm::vec4(0, 1, 1, 1));

	colours.push_back(glm::vec4(1, 1, 1, 1));
	colours.push_back(glm::vec4(1, 1, 1, 1));
	colours.push_back(glm::vec4(1, 0, 0, 1));
	colours.push_back(glm::vec4(1, 0, 1, 1));

	colours.push_back(glm::vec4(0, 0, 0, 1));
	colours.push_back(glm::vec4(1, 0, 0, 1));
	colours.push_back(glm::vec4(1, 1, 0, 1));
	colours.push_back(glm::vec4(0, 1, 0, 1));

	colours.push_back(glm::vec4(0, 0, 0, 1));
	colours.push_back(glm::vec4(0, 0, 1, 1));
	colours.push_back(glm::vec4(0, 1, 1, 1));
	colours.push_back(glm::vec4(0, 1, 0, 1));

	colours.push_back(glm::vec4(1, 1, 1, 1));
	colours.push_back(glm::vec4(0, 1, 1, 1));
	colours.push_back(glm::vec4(0, 1, 0, 1));
	colours.push_back(glm::vec4(1, 1, 0, 1));

	colours.push_back(glm::vec4(0, 0, 0, 1));
	colours.push_back(glm::vec4(1, 0, 0, 1));
	colours.push_back(glm::vec4(1, 0, 1, 1));
	colours.push_back(glm::vec4(0, 0, 1, 1));

	return colours;
}