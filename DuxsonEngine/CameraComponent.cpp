#include <GL/glew.h>
#include "./Include/CameraComponent.h"
#include "./Include/IVisualEngine.h"
#include "./Include/IEntity.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace DE;

CameraComponent::CameraComponent(const glm::mat4& projection, const ViewportParams& viewport)
	: VisualEntityComponent()
	, m_projMatrix(projection)
	, m_viewPortParams(viewport)
	, m_clearColour(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f))
	, m_renderOrder(eRender)
{
	m_clearBitMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::setClearMask(unsigned int clearMask)
{
	m_clearBitMask = clearMask;
}

void CameraComponent::setClearColour(const glm::vec4& clearColour)
{
	m_clearColour = clearColour;
}

void CameraComponent::setRenderOrder(RenderOrder renderOrder)
{
	m_renderOrder = renderOrder;
}

RenderOrder CameraComponent::getRenderOrder()
{
	return m_renderOrder;
}

void CameraComponent::update(IVisualEngine::SPtr visualEngine, float dtSecs)
{

}

void CameraComponent::render(IVisualEngine::SPtr visualEngine) const
{
	//We dont want to render anything in the usual way. Just set
	//setup viewport, clear relevant items and set uniforms.

	if (visualEngine != nullptr && (!m_parent.expired()))
	{
		visualEngine->clear(m_clearBitMask, m_clearColour);

		//Setup the viewport
		IWindow::SPtr window = visualEngine->getUtilities().getWindow();

		if (window != nullptr)
		{
			if (m_viewPortParams.useFullWindow)
				visualEngine->setViewport(0, 0, window->getWidth(), window->getHeight());
			else
				visualEngine->setViewport(m_viewPortParams.x, m_viewPortParams.y, m_viewPortParams.width, m_viewPortParams.height);
		}

		//View matrix is inverse of the camera's transformation matrix.
		glm::mat4 viewMatrix = glm::inverse(m_parent.lock()->getWorldTransform().getTransformation());

		visualEngine->getShaderUniformMap().set("DEProjectionMatrix", m_projMatrix);
		visualEngine->getShaderUniformMap().set("DEViewMatrix", viewMatrix);
		visualEngine->getShaderUniformMap().set("DEViewProjectionMatrix", m_projMatrix * viewMatrix);
	}
}