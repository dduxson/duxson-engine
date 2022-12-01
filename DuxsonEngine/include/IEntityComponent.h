/*!********************************************************************
* File:	IEntityComponent.h
*
* \brief	Interface that represents a basic entity component in the
*			Duxson Engine
* \details	Entities are made up of components which define that entity.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once
#include <memory>
#include "BoundingBox.h"

namespace DE
{
	class IEntity;

	class IEntityComponent
	{
		public:
			typedef std::shared_ptr<IEntityComponent> SPtr;

			IEntityComponent() {}
			virtual ~IEntityComponent() {}

			virtual void setParent(std::shared_ptr<IEntity> parent) = 0;
			virtual BoundingBox boundingBox() const = 0;
	};
}