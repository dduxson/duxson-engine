#pragma once

#include "ModelVisualEntityComponent.h"
#include "IModel.h"
#include "IShaderProgram.h"

namespace DE
{
	class VisualEntityRotatorComponent : public ModelVisualEntityComponent
	{
	public:
		VisualEntityRotatorComponent(IModel::SPtr model, IShaderProgram::SPtr prog);
		virtual ~VisualEntityRotatorComponent();

		virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs);
	};
}