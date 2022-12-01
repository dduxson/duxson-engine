/*!********************************************************************
* File:	IModel.h
*
* \brief	Interface that holds a full model consisting of multiple
*			meshes and materials.
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
	class IVisualEngine;

	class IModel
	{
		public:
			typedef std::shared_ptr<IModel> SPtr;

			IModel() {}
			virtual ~IModel() {}

			virtual void draw(std::shared_ptr<IVisualEngine> visualEngine) const = 0;
			virtual BoundingBox getBoundingBox() const = 0;
	};
}