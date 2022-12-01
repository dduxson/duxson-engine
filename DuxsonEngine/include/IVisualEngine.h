/*!********************************************************************
* File:	IVisualEngine.h
*
* \brief	Interface representing the visual engine that coordinates
*			the visuals for a IWindow.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include <map>
#include <glm/glm.hpp>
#include "IEntity.h"
#include "ShaderVariableMap.h"
#include "VisualEngineUtilities.h"

namespace DE
{
	enum RenderOrder
	{
		ePreRender,
		eRender,
		ePostRender
	};

	class IVisualEngine : public std::enable_shared_from_this<IVisualEngine>
	{
		public:
			typedef std::shared_ptr<IVisualEngine> SPtr;
			typedef std::weak_ptr<IVisualEngine> WPtr;

			IVisualEngine() {}
			virtual ~IVisualEngine() {}

			virtual void clear(unsigned int clearMask, const glm::vec4& clearColour) = 0;
			virtual void update(IEntity::SPtr root, float dtSecs) = 0;
			virtual void render(IEntity::SPtr root) = 0;

			virtual void setUtilities(const VisualEngineUtilities& utilities) = 0;
			virtual void setShaderUniformMap(const ShaderVariableMap& map) = 0;
			virtual void setSamplerSlot(const std::string& name, unsigned int value) = 0;
			virtual void setAmbientLighting(const glm::vec4& ambientIntensity) = 0;
			virtual void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) = 0;
			virtual void setClearColour(const glm::vec4& col) = 0;

			virtual unsigned int getSamplerSlot(const std::string& name) = 0;
			virtual ShaderVariableMap& getShaderUniformMap() = 0;
			virtual VisualEngineUtilities& getUtilities() = 0;
	};
}
