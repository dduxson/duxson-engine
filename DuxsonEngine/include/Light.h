/*!********************************************************************
* File:	Light.h
*
* \brief	Base class that can be used to represent a light in the
*			world. This class contains all parameters that a light
*			must have.
*
* \author	David Duxson
*
* \date	22/12/2015
*
**********************************************************************/
#pragma once
#include <glm/glm.hpp>
#include "VisualEntityComponent.h"

namespace DE
{
	class Light : public VisualEntityComponent
	{
		public:
			/*!
			*	\brief	Constructor for Light class.
			*/
			Light(const glm::vec3& colour, float intensity);

			/*!
			*	\brief	Destructor for Light class.
			*/
			virtual ~Light();

			/*!
			*	\brief	Sets the colour of this light.
			*	\param[in] colour Vec3 of the light colour.
			*/
			void setColour(const glm::vec3& colour);

			/*!
			*	\brief	Sets the intensity of this light
			*	\param[in] intensity The intensity as a float.
			*/
			void setIntensity(float intensity);

			/*!
			*	\brief	Sets whether this light is active (on).
			*	\param[in] active True if the light is on, false otherwise.
			*/
			void setActive(bool active);

			/*!
			*	\brief	Gets the colour of this light.
			*	\return Vec3 representing colour of the light.
			*/
			glm::vec3 getColour();

			/*!
			*	\brief	Gets the intensity of this light
			*	return  The intensity as a float.
			*/
			float getIntensity();

			/*!
			*	\brief	Gets whether this light is active (on).
			*	\return True if the light is on, false otherwise.
			*/
			bool getActive();

			/*!
			* \see IVisualEntityComponent
			*/
			virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs) {}

			/*!
			* \see IVisualEntityComponent
			*/
			virtual void render(IVisualEngine::SPtr visualEngine) const {}

		protected:
			glm::vec3 m_colour;			///< The colour of the light.
			float	  m_intensity;		///< The intensity of the light.
			bool	  m_active;			///< Should be true if the light is on.
		};
}