#include "./Include/RenderVisualEntityVisitor.h"
#include "./Include/IVisualEntityComponent.h"
#include "./Include/IVisualEngine.h"
#include "./Include/IEntity.h"
#include "./Include/CameraComponent.h"

using namespace DE;

RenderVisualEntityVisitor::RenderVisualEntityVisitor()
	: m_renderPass(eRender)
	, m_currentRenderOrder(eRender)
{

}

RenderVisualEntityVisitor::~RenderVisualEntityVisitor()
{

}

void RenderVisualEntityVisitor::setRenderPass(RenderOrder renderPass)
{
	m_renderPass = renderPass;
}

void RenderVisualEntityVisitor::setVisualEngine(std::shared_ptr<IVisualEngine> visualEngine)
{
	m_visualEngine = visualEngine;
}

void RenderVisualEntityVisitor::apply(std::shared_ptr<IEntity> node)
{
	if (node == nullptr || m_visualEngine.expired())
		return;

	IVisualEngine::SPtr visualEngine = m_visualEngine.lock();
	std::vector<IEntityComponent::SPtr> components = node->getComponents();

	//2 loop overs - detect if render order is this pass, then apply all components if it is.
	RenderOrder lastRenderOrder = m_currentRenderOrder;
	ShaderVariableMap lastVariableMap = visualEngine->getShaderUniformMap();

	for (unsigned int i = 0; i < components.size(); ++i)
	{
		CameraComponent::SPtr camComponent = std::dynamic_pointer_cast<CameraComponent>(components[i]);

		if (camComponent)
		{
			m_currentRenderOrder = camComponent->getRenderOrder();
			break;
		}
	}

	if (m_currentRenderOrder == m_renderPass)
	{
		for (unsigned int i = 0; i < components.size(); ++i)
		{
			IVisualEntityComponent::SPtr visualComponent = std::dynamic_pointer_cast<IVisualEntityComponent>(components[i]);

			if (visualComponent)
				visualComponent->render(visualEngine);
		}
	}

	node->traverse(shared_from_this());

	//Reset
	m_currentRenderOrder = lastRenderOrder;
	visualEngine->setShaderUniformMap(lastVariableMap);
}
