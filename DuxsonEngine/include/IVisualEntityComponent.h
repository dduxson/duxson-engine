/*!********************************************************************
* File:	IVisualEntityComponent.h
*
* \brief	Interface components that should be updated/rendered by
*			the visual engine.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include "IEntityComponent.h"
#include "IVisualEngine.h"

namespace DE
{
	class IVisualEntityComponent : public IEntityComponent
	{
		public:
			typedef std::shared_ptr<IVisualEntityComponent> SPtr;

			IVisualEntityComponent() : IEntityComponent() {}

			virtual ~IVisualEntityComponent() {}

			virtual void update(IVisualEngine::SPtr visualEngine, float dtSecs) = 0;
			virtual void render(IVisualEngine::SPtr visualEngine) const = 0;
	};
}
