#include "./Include/ModelVisualEntityComponent.h"
#include "./Include/VisualEngine.h"
#include "./Include/Entity.h"

namespace DE
{
	ModelVisualEntityComponent::ModelVisualEntityComponent(IModel::SPtr model, IShaderProgram::SPtr prog)
		: VisualEntityComponent()
		, m_model(model)
		, m_shaderProgram(prog)
	{

	}

	ModelVisualEntityComponent::ModelVisualEntityComponent()
		: VisualEntityComponent()
	{
	}

	ModelVisualEntityComponent::~ModelVisualEntityComponent()
	{
	}

	void ModelVisualEntityComponent::setRenderState(IRenderState::SPtr state)
	{
		m_states.push_back(state);
	}

	void ModelVisualEntityComponent::update(IVisualEngine::SPtr visualEngine, float dtSecs)
	{

	}

	void ModelVisualEntityComponent::render(IVisualEngine::SPtr visualEngine) const
	{
		//Set built in uniform for parent's transformation
		//Also send a normal matrix of 3x3.
		if (visualEngine != nullptr && (!m_parent.expired()))
		{
			visualEngine->getShaderUniformMap().set("DEModelMatrix", m_parent.lock()->getWorldTransform().getTransformation());
			visualEngine->getShaderUniformMap().set("DENormalMatrix", glm::mat3(m_parent.lock()->getWorldTransform().getTransformation()));
		}

		for (unsigned int i = 0; i < m_states.size(); ++i)
			m_states[i]->enable();

		if (m_shaderProgram != nullptr)
		{
			m_shaderProgram->bind();
			m_shaderProgram->updateUniforms(visualEngine);
		}

		if (m_model != nullptr)
			m_model->draw(visualEngine);

		for (unsigned int i = 0; i < m_states.size(); ++i)
			m_states[i]->disable();
	}

	BoundingBox ModelVisualEntityComponent::boundingBox() const
	{
		if (!m_model)
			BoundingBox();

		return m_model->getBoundingBox();
	}
}