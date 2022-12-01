#include "SimpleTerrainSimulation.h"
#include "../DuxsonEngine/Include/DirectionalLight.h"
#include "../DuxsonEngine/Include/CameraComponent.h"
#include "../DuxsonEngine/Include/TerrainHeightMapKeyboardMoveComponent.h"
#include "../DuxsonEngine/Include/MouseLookComponent.h"
#include "../DuxsonEngine/Include/TerrainHeightMapComponent.h"
#include "../DuxsonEngine/include/Entity.h"
#include "../DuxsonEngine/include/ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

SimpleTerrainSimulation::SimpleTerrainSimulation()
{

}

SimpleTerrainSimulation::~SimpleTerrainSimulation()
{

}

bool SimpleTerrainSimulation::init(DE::IVisualEngine::SPtr visualEngine)
{
	//Setup Scene graph
	m_root = std::make_shared<DE::Entity>();

	//Setup a camera and enable it to move around
	DE::IEntity::SPtr mainCam = std::make_shared<DE::Entity>();
	mainCam->addComponent(std::make_shared<DE::MouseLookComponent>());
	mainCam->addComponent(std::make_shared<DE::CameraComponent>(glm::perspective(45.0f, visualEngine->getUtilities().getWindow()->getAspect(), 0.1f, 1000.0f)));
	mainCam->setParent(m_root);

	//Setup a directional light (intial direction is +x so rotate 90 around x axis to point diagonally downwards)
	DE::IEntity::SPtr dirLight = std::make_shared<DE::Entity>(true, glm::vec3(0, 0, 0), glm::angleAxis(glm::radians(45.0f), glm::vec3(1, 0, 0)));
	dirLight->addComponent(std::make_shared<DE::DirectionalLight>(1, glm::vec3(1.0, 1.0, 1.0)));
	dirLight->setParent(mainCam);

	//Setup our terrain
	DE::IEntity::SPtr terrain = std::make_shared<DE::Entity>(true, glm::vec3(0.0f, 0.0f, 0.00), glm::quat(), glm::vec3(300, 35, 300));
	DE::IEntityComponent::SPtr terrainHeightMap = std::make_shared<DE::TerrainHeightMapComponent>(std::string("./Data/Textures/heightMap.jpg"), std::string("./Data/Textures/grassTexture.jpg"), std::make_shared<DE::ShaderProgram>("./Data/Shaders/oneDirLightAndTex.prog"));
	terrain->addComponent(terrainHeightMap);
	terrain->setParent(dirLight);
	mainCam->addComponent(std::make_shared<DE::TerrainHeightMapKeyboardMoveComponent>(std::dynamic_pointer_cast<DE::TerrainHeightMapComponent>(terrainHeightMap)));

	return true;
}