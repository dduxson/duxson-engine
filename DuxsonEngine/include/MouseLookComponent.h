/*!********************************************************************
* File:	MouseLookComponent.h
*
* \brief	Class that handles free looking of the mouse. Note that
*			this component will completly override whatever rotation
*			is set for the entity this is attached to but will leave
*			the translation alone - BE CAREFUL!
*
* \author	David Duxson
*
* \date	20/12/2015
*
**********************************************************************/
#pragma once
#include "VisualEntityComponent.h"

namespace DE
{
	class MouseLookComponent : public VisualEntityComponent
	{
		public:
			MouseLookComponent(float horizontalAngle = 0.0f, float verticalAngle = 3.14159265359, float sensitivity = 0.5f);

			virtual ~MouseLookComponent();

			virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs);
			virtual void render(IVisualEngine::SPtr visualEngine) const;

		private:
			void setNewRotMatrix(const Transform& transform, float verticalAngle, float horizontalAngle);

		private:
			float m_sensitivity;
			bool  m_firstTime;

			float m_verticalAngle;
			float m_horizontalAngle;
		};
}