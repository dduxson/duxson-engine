#include "./Include/UpdateVisualEntityVisitor.h"
#include "./Include/IVisualEntityComponent.h"
#include "./Include/IVisualEngine.h"
#include "./Include/IEntity.h"

using namespace DE;

UpdateVisualEntityVisitor::UpdateVisualEntityVisitor()
	: m_dtSecs(0.0f)
{

}

UpdateVisualEntityVisitor::~UpdateVisualEntityVisitor()
{

}

void UpdateVisualEntityVisitor::setDeltaSecs(float dtSecs)
{
	m_dtSecs = dtSecs;
}

void UpdateVisualEntityVisitor::setVisualEngine(std::shared_ptr<IVisualEngine> visualEngine)
{
	m_visualEngine = visualEngine;
}

void UpdateVisualEntityVisitor::apply(std::shared_ptr<IEntity> node)
{
	if (node)
	{
		std::vector<IEntityComponent::SPtr> components = node->getComponents();

		for (unsigned int i = 0; i < components.size(); ++i)
		{
			IVisualEntityComponent::SPtr visualComponent = std::dynamic_pointer_cast<IVisualEntityComponent>(components[i]);

			if (visualComponent != nullptr && (!m_visualEngine.expired()))
				visualComponent->update(m_visualEngine.lock(), m_dtSecs);
		}
	}

	node->traverse(shared_from_this());
}
