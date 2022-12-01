#include "MazeLevel.h"
#include "../DuxsonEngine/Include/DirectionalLight.h"
#include "../DuxsonEngine/Include/CameraComponent.h"
#include "../DuxsonEngine/Include/KeyboardMoveComponent.h"
#include "../DuxsonEngine/Include/MouseLookComponent.h"
#include "../DuxsonEngine/include/ShaderProgram.h"
#include "../DuxsonEngine/include/ModelVisualEntityComponent.h"
//#include "../DuxsonEngine/Include/TextComponent.h"
#include "PlayerComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>

MazeLevel::MazeLevel()
{
	std::srand(unsigned int(std::time(NULL)));

	m_maze = std::make_shared<Maze>();
	m_collisionSystem = std::make_shared<CollisionSystem>(m_maze);
}

MazeLevel::~MazeLevel()
{
	
}

bool MazeLevel::init(DE::IVisualEngine::SPtr visualEngine)
{
	m_threeDGen.setFloorTextureFile(std::string("./Data/Textures/Ground.bmp"));
	m_threeDGen.setWallTextureFile(std::string("./Data/Textures/Wall1.bmp"));

	//TEST
	m_mapHudBuilder.setHUDBackgroundTexture(std::string("./Data/Textures/mazeMapHudBackground.png"));
	m_mapHudBuilder.setHUDBackgroundShader(std::string("./Data/Shaders/diffuseTex.prog"));
	m_mapHudBuilder.setViewport(DE::ViewportParams(0, 0, visualEngine->getUtilities().getWindow()->getWidth() / 4, visualEngine->getUtilities().getWindow()->getHeight() / 4));

	createLevel(50, visualEngine);

	return true;
}

void MazeLevel::createLevel(unsigned int levelNum, DE::IVisualEngine::SPtr visualEngine)
{
	if (levelNum == 0 || m_maze == NULL)
	{
		DE::Logger::Instance()->writeToLogFile(DE::Logger::eLogError, "Failed to create level!");
		return;
	}

	m_maze->setSize(levelNum + 1, levelNum + 1);
	m_maze->generateMaze();

	//Setup Scene graph
	m_root = std::make_shared<DE::Entity>();

	DE::IEntity::SPtr mainCam = std::make_shared<DE::Entity>(true, glm::vec3(2.25f, 2.0f, -2.25f));
	mainCam->setParent(m_root);

	PlayerComponent::SPtr playerComponent = std::make_shared<PlayerComponent>();
	playerComponent->setMazeIn(m_maze);
	playerComponent->setCollisionSystem(m_collisionSystem);

	mainCam->addComponent(playerComponent);
	mainCam->addComponent(std::make_shared<DE::MouseLookComponent>());
	mainCam->addComponent(std::make_shared<DE::CameraComponent>(glm::perspective(45.0f, visualEngine->getUtilities().getWindow()->getAspect(), 0.1f, 1000.0f)));

	DE::IEntity::SPtr dirLight = std::make_shared<DE::Entity>(true, glm::vec3(0, 0, 0), glm::angleAxis(glm::radians(90.0f), glm::vec3(1, 0, 0)));
	dirLight->addComponent(std::make_shared<DE::DirectionalLight>(1, glm::vec3(0.8, 0.8, 0.8)));
	dirLight->setParent(mainCam);

	DE::IEntity::SPtr mazeThreeD = m_threeDGen.generateEntity(*m_maze);
	dirLight->addChild(mazeThreeD);

	//TEST ONLY
	DE::IEntity::SPtr testMesh = std::make_shared<DE::Entity>(true, glm::vec3(2.25f, 2.0f, -6.75f));
	testMesh->addComponent(std::make_shared<DE::ModelVisualEntityComponent>(std::make_shared<DE::Model>("./Data/Models/SpaceInvaderA1.obj"),
																		std::make_shared<DE::ShaderProgram>("./Data/Shaders/oneDirLightAndTex.prog")));
	testMesh->setParent(mazeThreeD);

	//Map HUD
	m_mapHudBuilder.setEntity(mainCam);
	DE::IEntity::SPtr mazeTwoD = m_mapHudBuilder.generateEntity(*m_maze);
	m_root->addChild(mazeTwoD);

	//Level Text
	DE::IEntity::SPtr orthoCamEntity = std::make_shared<DE::Entity>(true);
	DE::CameraComponent::SPtr orthoCam = std::make_shared<DE::CameraComponent>(glm::ortho(0.0f, float(visualEngine->getUtilities().getWindow()->getWidth()), 0.0f, float(visualEngine->getUtilities().getWindow()->getHeight())));
	orthoCam->setClearMask(GL_DEPTH_BUFFER_BIT);
	orthoCam->setRenderOrder(DE::ePostRender);
	orthoCamEntity->addComponent(orthoCam);
	orthoCamEntity->setParent(m_root);

	DE::IEntity::SPtr levelText = std::make_shared<DE::Entity>(true, glm::vec3(visualEngine->getUtilities().getWindow()->getWidth() / 2.0f, visualEngine->getUtilities().getWindow()->getHeight(), 0));
	//levelText->addComponent(new DE::TextComponent("Test Level", "./Data/Fonts/arial.ttf", 50, visualEngine, new DE::ShaderProgram("./Data/Shaders/text.prog")));
	levelText->setParent(orthoCamEntity);
}
