#include "./Include/Light.h"

namespace DE
{
	Light::Light(const glm::vec3& colour, float intensity)
		: VisualEntityComponent()
		, m_colour(colour)
		, m_intensity(intensity)
		, m_active(true)
	{

	}

	Light::~Light()
	{

	}

	void Light::setColour(const glm::vec3& colour)
	{
		m_colour = colour;
	}

	void Light::setIntensity(float intensity)
	{
		m_intensity = intensity;
	}

	void Light::setActive(bool active)
	{
		m_active = active;
	}

	glm::vec3 Light::getColour()
	{
		return m_colour;
	}

	float Light::getIntensity()
	{
		return m_intensity;
	}

	bool Light::getActive()
	{
		return m_active;
	}
}