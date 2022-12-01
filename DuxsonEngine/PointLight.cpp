#include "./Include/PointLight.h"
#include <sstream>

namespace DE
{
	PointLight::PointLight(unsigned int pointLightId, const glm::vec3& colour, float intensity, const Attenuation& attenuation)
		: Light(colour, intensity)
		, m_pointLightId(pointLightId)
		, m_attenuation(attenuation)
	{
		//Convert id to string for easy access later.
		std::stringstream ss;
		ss << m_pointLightId;

		m_strPointLightId = ss.str();

		float colour_depth = 256;
		float max_colour = glm::max(glm::max(colour.x, colour.y), colour.z);

		float a = m_attenuation.getExponent();
		float b = m_attenuation.getLinear();
		float c = m_attenuation.getConstant() - colour_depth * intensity * max_colour;

		m_range = (-b + sqrtf(b*b - 4 * a*c)) / (2 * a); //Quadratic equation solution.
	}

	PointLight::~PointLight()
	{

	}

	void PointLight::update(IVisualEngine::SPtr visualEngine, float dtSecs)
	{

	}

	void PointLight::render(IVisualEngine::SPtr visualEngine) const
	{
		//Set uniforms for this light
		//For now we cannot handle arrays, so each light is a separate uniform.
		if (visualEngine && (!m_parent.expired()))
		{
			std::string firstUniformName = "DEPointLight" + m_strPointLightId;

			const Transform& transform = m_parent.lock()->getWorldTransform();

			visualEngine->getShaderUniformMap().set(firstUniformName + ".base.colour", m_colour);
			visualEngine->getShaderUniformMap().set(firstUniformName + ".base.intensity", m_intensity);
			visualEngine->getShaderUniformMap().set(firstUniformName + ".base.active", m_active);
			visualEngine->getShaderUniformMap().set(firstUniformName + ".position", transform.getTrans());
			visualEngine->getShaderUniformMap().set(firstUniformName + ".range", m_range);
			visualEngine->getShaderUniformMap().set(firstUniformName + ".attenuation.constant", m_attenuation.getConstant());
			visualEngine->getShaderUniformMap().set(firstUniformName + ".attenuation.linear", m_attenuation.getLinear());
			visualEngine->getShaderUniformMap().set(firstUniformName + ".attenuation.exponent", m_attenuation.getExponent());
		}
	}
}