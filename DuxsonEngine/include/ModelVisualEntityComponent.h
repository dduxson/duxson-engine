#pragma once

#include <vector>
#include "VisualEntityComponent.h"
#include "IShaderProgram.h"
#include "IModel.h"
#include "IRenderState.h"

namespace DE
{
	class ModelVisualEntityComponent : public VisualEntityComponent
	{
		public:
			typedef std::shared_ptr<ModelVisualEntityComponent> SPtr;

			ModelVisualEntityComponent(IModel::SPtr model, IShaderProgram::SPtr prog);
			ModelVisualEntityComponent();

			virtual ~ModelVisualEntityComponent();

			void setRenderState(IRenderState::SPtr state);

			virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs);
			virtual void render(IVisualEngine::SPtr visualEngine) const;
			virtual BoundingBox boundingBox() const;

		protected:
			IModel::SPtr					m_model;
			IShaderProgram::SPtr			m_shaderProgram;
			std::vector<IRenderState::SPtr>	m_states;
	};
}