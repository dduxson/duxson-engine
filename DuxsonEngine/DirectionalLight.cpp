#include "./Include/DirectionalLight.h"
#include <sstream>

namespace DE
{
	DirectionalLight::DirectionalLight(unsigned int dirLightId, const glm::vec3& colour, float intensity)
		: Light(colour, intensity)
		, m_dirLightId(dirLightId)
	{
		//Convert id to string for easy access later.
		std::stringstream ss;
		ss << m_dirLightId;

		m_strDirLightId = ss.str();
	}

	DirectionalLight::~DirectionalLight()
	{

	}

	void DirectionalLight::update(IVisualEngine::SPtr visualEngine, float dtSecs)
	{

	}

	void DirectionalLight::render(IVisualEngine::SPtr visualEngine) const
	{
		//Set uniforms for this light
		//For now we cannot handle arrays, so each light is a separate uniform.
		if (visualEngine && (!m_parent.expired()))
		{
			std::string firstUniformName = "DEDirectionalLight" + m_strDirLightId;

			const Transform& transform = m_parent.lock()->getTransform();

			visualEngine->getShaderUniformMap().set(firstUniformName + ".base.colour", m_colour);
			visualEngine->getShaderUniformMap().set(firstUniformName + ".base.intensity", m_intensity);
			visualEngine->getShaderUniformMap().set(firstUniformName + ".base.active", m_active);
			visualEngine->getShaderUniformMap().set(firstUniformName + ".direction", transform.getForwardDir());
		}
	}
}