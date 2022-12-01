#include "HUDBuilder.h"
#include "../DuxsonEngine/Include/ModelVisualEntityComponent.h"
#include "../DuxsonEngine/Include/Blending.h"
#include "../DuxsonEngine/include/Geometry.h"
#include "../DuxsonEngine/include/Mesh.h"
#include "../DuxsonEngine/include/ShaderProgram.h"
#include "../DuxsonEngine/include/Material.h"
#include "../DuxsonEngine/include/Model.h"
#include <glm/gtc/matrix_transform.hpp>

HUDBuilder::HUDBuilder()
	: m_orthoLeft(0.0f)
	, m_orthoRight(1.01f)
	, m_orthoBottom(0.0f)
	, m_orthoTop(1.01f)
	, m_quadName("HUDQuad")
{
	m_viewportParams = DE::ViewportParams();
}

HUDBuilder::~HUDBuilder()
{

}

void HUDBuilder::setHUDBackgroundTexture(const std::string& texFilename)
{
	m_texFilename = texFilename;
}

void HUDBuilder::setHUDBackgroundShader(const std::string& filename)
{
	m_shaderProgFilename = filename;
}

void HUDBuilder::setViewport(const DE::ViewportParams& params)
{
	m_viewportParams = params;
}

void HUDBuilder::setHUDOrthoProjectionMatrix(float left, float right, float bottom, float top)
{
	m_orthoLeft = left;
	m_orthoRight = right;
	m_orthoBottom = bottom;
	m_orthoTop = top;
}

DE::Entity::SPtr HUDBuilder::generateQuad()
{
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indicies;
	std::vector<glm::vec2> texCoords;

	indicies.push_back(0);
	indicies.push_back(2);
	indicies.push_back(1);
	indicies.push_back(1);
	indicies.push_back(2);
	indicies.push_back(3);

	vertices.push_back(glm::vec3(m_orthoRight, m_orthoBottom, 0.0f));
	vertices.push_back(glm::vec3(m_orthoRight, m_orthoTop, 0.0f));
	vertices.push_back(glm::vec3(m_orthoLeft, m_orthoBottom, 0.0f));
	vertices.push_back(glm::vec3(m_orthoLeft, m_orthoTop, 0.0f));

	texCoords.push_back(glm::vec2(1, 0));
	texCoords.push_back(glm::vec2(1, 1));
	texCoords.push_back(glm::vec2(0, 0));
	texCoords.push_back(glm::vec2(0, 1));

	DE::Geometry::SPtr geom = std::make_shared<DE::Geometry>(indicies, vertices, texCoords);

	DE::ModelVisualEntityComponent::SPtr visComp = std::make_shared<DE::ModelVisualEntityComponent>(std::make_shared<DE::Model>(std::make_shared<DE::Mesh>(m_quadName, geom),
																																std::make_shared<DE::Material>(DE::TextureParams(m_texFilename))),
																									std::make_shared<DE::ShaderProgram>(m_shaderProgFilename));
	visComp->setRenderState(std::make_shared<DE::Blending>(true));

	DE::Entity::SPtr quadEntity = std::make_shared<DE::Entity>();
	quadEntity->setAbsoluteCoords(true);
	quadEntity->addComponent(visComp);

	return quadEntity;
}

DE::Entity::SPtr HUDBuilder::createHudCam()
{
	DE::CameraComponent::SPtr camComponent = std::make_shared<DE::CameraComponent>(glm::ortho(m_orthoLeft, m_orthoRight, m_orthoBottom, m_orthoTop), m_viewportParams);
	camComponent->setClearMask(GL_DEPTH_BUFFER_BIT);
	camComponent->setRenderOrder(DE::ePostRender);

	DE::Entity::SPtr camera = std::make_shared<DE::Entity>();
	camera->addComponent(camComponent);

	return camera;
}

DE::Entity::SPtr HUDBuilder::generateEntity(const Maze &maze)
{
	if (m_texFilename.size() == 0 || m_shaderProgFilename.size() == 0)
		return NULL;

	DE::Entity::SPtr background = generateQuad();
	DE::Entity::SPtr camera = createHudCam();
	camera->addChild(background);

	return camera;
}