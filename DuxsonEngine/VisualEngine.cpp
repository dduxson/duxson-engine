#include <GL/glew.h>
#include "./Include/VisualEngine.h"

namespace DE
{
	VisualEngine::VisualEngine()
		: m_clearColour(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f))
	{
		//Setup sampler units for different types of textures.
		setSamplerSlot("DEDiffuse1", 0);
		setAmbientLighting(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

		initGL();
	}

	VisualEngine::~VisualEngine()
	{

	}

	void VisualEngine::setClearColour(const glm::vec4 &col)
	{
		m_clearColour = col;
	}

	void VisualEngine::initGL()
	{
		glClearColor(m_clearColour.x, m_clearColour.y, m_clearColour.z, m_clearColour.w);

		/*glFrontFace(GL_CCW);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);*/
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LEQUAL);
		glDepthRange(0.0f, 1.0f);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void VisualEngine::clear(unsigned int clearMask, const glm::vec4& clearColour)
	{
		glClearColor(clearColour.x, clearColour.y, clearColour.z, clearColour.w);
		glClear(clearMask);
	}

	void VisualEngine::setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	void VisualEngine::update(IEntity::SPtr root, float dtSecs)
	{
		if (m_utilities.getUpdateVisitor() != nullptr)
		{
			m_utilities.getUpdateVisitor()->setDeltaSecs(dtSecs);
			m_utilities.getUpdateVisitor()->apply(root);
		}
	}

	void VisualEngine::render(IEntity::SPtr root)
	{
		clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, m_clearColour);

		if (m_utilities.getRenderVisitor() != nullptr)
		{
			m_utilities.getRenderVisitor()->setRenderPass(ePreRender);
			m_utilities.getRenderVisitor()->apply(root);

			m_utilities.getRenderVisitor()->setRenderPass(eRender);
			m_utilities.getRenderVisitor()->apply(root);

			m_utilities.getRenderVisitor()->setRenderPass(ePostRender);
			m_utilities.getRenderVisitor()->apply(root);
		}
	}

	ShaderVariableMap& VisualEngine::getShaderUniformMap()
	{
		return m_ShaderUniformMap;
	}

	void VisualEngine::setUtilities(const VisualEngineUtilities & utilities)
	{
		m_utilities = utilities;
		
		if (m_utilities.getUpdateVisitor() != nullptr)
			m_utilities.getUpdateVisitor()->setVisualEngine(shared_from_this());
		if (m_utilities.getRenderVisitor() != nullptr)
			m_utilities.getRenderVisitor()->setVisualEngine(shared_from_this());
	}

	void VisualEngine::setShaderUniformMap(const ShaderVariableMap& map)
	{
		m_ShaderUniformMap = map;
	}

	unsigned int VisualEngine::getSamplerSlot(const std::string& name)
	{
		std::map<std::string, unsigned int>::const_iterator it = m_samplerNameToSlot.find(name);

		if (it != m_samplerNameToSlot.end())
			return it->second;
		else
			return 0;
	}

	void VisualEngine::setSamplerSlot(const std::string& name, unsigned int value)
	{
		m_samplerNameToSlot[name] = value;
	}

	VisualEngineUtilities& VisualEngine::getUtilities()
	{
		return m_utilities;
	}

	void VisualEngine::setAmbientLighting(const glm::vec4& ambientIntensity)
	{
		m_ShaderUniformMap.set("ambientIntensity", ambientIntensity);
	}
}