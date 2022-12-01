#pragma once
/*!********************************************************************
* File:	PointLight.h
*
* \brief	Light that will shine from a specific point. It will get
*			the position of the parent entity.
*
* \author	David Duxson
*
* \date	22/12/2015
*
**********************************************************************/
#include "Light.h"
#include "Attenuation.h"
#include <vector>

namespace DE
{
	class PointLight : public Light
	{
	public:
		/*!
		*	\brief	Constructor for PointLight class.
		*/
		PointLight(unsigned int pointLightId, const glm::vec3& colour = glm::vec3(1, 1, 1), float intensity = 1.0f, const Attenuation& = Attenuation());

		/*!
		*	\brief	Destructor for PointLight class.
		*/
		virtual ~PointLight();

		/*!
		* \see IVisualEntityComponent
		*/
		virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs);

		/*!
		* \see IVisualEntityComponent
		*/
		virtual void render(IVisualEngine::SPtr visualEngine) const;

	private:
		unsigned int m_pointLightId;	///< The id of this point light - required for shader uniform.
		std::string m_strPointLightId;	///< The id of this point light as a string.
		Attenuation m_attenuation;		///< The attenuation parameters for this point light.
		float m_range;					///< The maximum range of the spot light (performance).
	};
}
