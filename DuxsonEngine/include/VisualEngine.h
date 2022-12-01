/*!********************************************************************
* File:	VisualEngine.h
*
* \brief	Class representing the visual engine that coordinates
*			the visuals for a IWindow.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include "IVisualEngine.h"

namespace DE
{
	class VisualEngine : public IVisualEngine
	{
		public:
			VisualEngine();
			virtual ~VisualEngine();

			void update(IEntity::SPtr root, float dtSecs);
			void render(IEntity::SPtr root);
			void clear(unsigned int clearMask, const glm::vec4& clearColour);
			
			void setUtilities(const VisualEngineUtilities& utilities);
			void setShaderUniformMap(const ShaderVariableMap& map);
			void setSamplerSlot(const std::string& name, unsigned int value);
			void setAmbientLighting(const glm::vec4& ambientIntensity);
			void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
			void setClearColour(const glm::vec4& col);

			ShaderVariableMap& getShaderUniformMap();
			unsigned int getSamplerSlot(const std::string& name);
			VisualEngineUtilities& getUtilities();

		private:
			void initGL();

		private:
			VisualEngineUtilities				m_utilities;
			glm::vec4							m_clearColour;
			ShaderVariableMap					m_ShaderUniformMap;
			std::map<std::string, unsigned int> m_samplerNameToSlot;
	};
}