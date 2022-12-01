#include "./include/VisualEntityRotatorComponent.h"

using namespace DE;

VisualEntityRotatorComponent::VisualEntityRotatorComponent(IModel::SPtr model, IShaderProgram::SPtr prog)
	: ModelVisualEntityComponent(model, prog)
{
}

VisualEntityRotatorComponent::~VisualEntityRotatorComponent()
{
}

void VisualEntityRotatorComponent::update(IVisualEngine::SPtr visualEngine, float dtSecs)
{
	if (!m_parent.expired())
	{
		const Transform& transform = m_parent.lock()->getTransform();

		m_parent.lock()->setRot(glm::rotate(transform.getRot(), dtSecs * 3, glm::vec3(0.5, 0.5, 0.5)));
	}
}
