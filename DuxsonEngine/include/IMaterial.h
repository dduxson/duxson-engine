/*!********************************************************************
* File:	IMaterial.h
*
* \brief	Interface that represents the whole material, this can be
*			multiple different textures with different parameters.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include <memory>

namespace DE
{
	class IVisualEngine;

	class IMaterial
	{
		public:
			typedef std::shared_ptr<IMaterial> SPtr;
			typedef std::weak_ptr<IMaterial> WPtr;

			IMaterial() {}
			virtual ~IMaterial() {}

			virtual void bindTextures(std::shared_ptr<IVisualEngine> visualEngine) = 0;
	};
}