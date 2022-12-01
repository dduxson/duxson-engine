/*!********************************************************************
* File:	DirectionalLight.h
*
* \brief	Light that will shine in a specific direction. It will get
*			the direction from the rotation of the parent entity.
*
* \author	David Duxson
*
* \date	22/12/2015
*
**********************************************************************/
#pragma once
#include "Light.h"
#include <vector>

namespace DE
{
	class DirectionalLight : public Light
	{
		public:
			/*!
			*	\brief	Constructor for DirectionalLight class.
			*/
			DirectionalLight(unsigned int dirLightId, const glm::vec3& colour = glm::vec3(1, 1, 1), float intensity = 1.0f);

			/*!
			*	\brief	Destructor for DirectionalLight class.
			*/
			virtual ~DirectionalLight();

			/*!
			* \see IVisualEntityComponent
			*/
			virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs);

			/*!
			* \see IVisualEntityComponent
			*/
			virtual void render(IVisualEngine::SPtr visualEngine) const;

		private:
			unsigned int m_dirLightId;		///< The id of this directional light - required for shader uniform.
			std::string m_strDirLightId;	///< The id of this directional light as a string.
	};
}