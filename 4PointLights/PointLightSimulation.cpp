#include "PointLightSimulation.h"
#include "../DuxsonEngine/include/VisualEntityRotatorComponent.h"
#include "../DuxsonEngine/include/ModelVisualEntityComponent.h"
#include "../DuxsonEngine/include/TerrainHeightMapComponent.h"
#include "../DuxsonEngine/Include/PointLight.h"
#include "../DuxsonEngine/Include/CameraComponent.h"
#include "../DuxsonEngine/Include/KeyboardMoveComponent.h"
#include "../DuxsonEngine/Include/MouseLookComponent.h"
#include "../DuxsonEngine/Include/CubeGeometry.h"
#include "../DuxsonEngine/Include/SphereGeometry.h"
#include "../DuxsonEngine/include/Entity.h"
#include "../DuxsonEngine/include/Model.h"
#include "../DuxsonEngine/include/Mesh.h"
#include "../DuxsonEngine/include/ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

PointLightSimulation::PointLightSimulation()
{

}

PointLightSimulation::~PointLightSimulation()
{

}

bool PointLightSimulation::init(DE::IVisualEngine::SPtr visualEngine)
{
	//Setup Scene graph
	m_root = std::make_shared<DE::Entity>();

	//Setup a camera and enable it to move around
	DE::IEntity::SPtr mainCam = std::make_shared<DE::Entity>();
	mainCam->addComponent(std::make_shared<DE::MouseLookComponent>());
	mainCam->addComponent(std::make_shared<DE::KeyboardMoveComponent>());
	mainCam->addComponent(std::make_shared<DE::CameraComponent>(glm::perspective(45.0f, visualEngine->getUtilities().getWindow()->getAspect(), 0.1f, 1000.0f)));
	mainCam->setParent(m_root);

	//Setup a point light
	DE::IEntity::SPtr pointLight = std::make_shared<DE::Entity>(true, glm::vec3(0, 0, 0));
	DE::IModel::SPtr sphereLightModel = std::make_shared<DE::Model>(std::make_shared<DE::Mesh>("sphereLight", std::make_shared<DE::SphereGeometry>(0.1f)), nullptr);
	pointLight->addComponent(std::make_shared<DE::ModelVisualEntityComponent>(sphereLightModel, std::make_shared<DE::ShaderProgram>("./Data/Shaders/onePointLightAndColour.prog")));
	pointLight->addComponent(std::make_shared<DE::PointLight>(1, glm::vec3(1.0, 1.0, 1.0)));
	pointLight->setParent(mainCam);

	//Setup our test sphere
	DE::IEntity::SPtr cube = std::make_shared<DE::Entity>(true, glm::vec3(0.0f, 0.0f, -4.00f));
	DE::IModel::SPtr sphereModel = std::make_shared<DE::Model>(std::make_shared<DE::Mesh>("sphere", std::make_shared<DE::SphereGeometry>(0.5f,glm::vec4(1,0,0,1))), nullptr);
	cube->addComponent(std::make_shared<DE::VisualEntityRotatorComponent>(sphereModel, std::make_shared<DE::ShaderProgram>("./Data/Shaders/onePointLightAndColour.prog")));
	cube->setParent(pointLight);

	//DE::IEntity::SPtr terrain = std::make_shared<DE::Entity>(true, glm::vec3(0.0f, 0.0f, 0.00), glm::quat(), glm::vec3(300, 35, 300));
	//DE::IEntityComponent::SPtr terrainHeightMap = std::make_shared<DE::TerrainHeightMapComponent>(std::string("./Data/Textures/heightMap.jpg"), std::string("./Data/Textures/grassTexture.jpg"), std::make_shared<DE::ShaderProgram>("./Data/Shaders/onePointLightAndTex.prog"));
	//terrain->addComponent(terrainHeightMap);
	//terrain->setParent(pointLight);

	return true;
}