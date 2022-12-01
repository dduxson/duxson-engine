/*!********************************************************************
* File:	VisualEntityComponent.h
*
* \brief	Class for components that should be updated/rendered by
*			the visual engine.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include "IVisualEntityComponent.h"

namespace DE
{
	class VisualEntityComponent : public IVisualEntityComponent
	{
		public:
			VisualEntityComponent() {}
			virtual ~VisualEntityComponent() {}

			virtual void setParent(std::shared_ptr<IEntity> parent) { m_parent = parent; }
			virtual BoundingBox boundingBox() const { return BoundingBox(); }

			virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs) {}
			virtual void render(IVisualEngine::SPtr visualEngine) const {}

			//Ensure no copy or assignability.
			VisualEntityComponent(const VisualEntityComponent& other) = delete;
			void operator=(const VisualEntityComponent& other) = delete;

		protected:
			std::weak_ptr<IEntity> m_parent;
	};
}