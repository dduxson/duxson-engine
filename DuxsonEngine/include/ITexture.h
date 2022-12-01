/*!********************************************************************
* File:	ITexture.h
*
* \brief	Interface that deals with a texture.
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
	class ITexture
	{
		public:
			typedef std::shared_ptr<ITexture> SPtr;

			ITexture() {}
			virtual ~ITexture() {}

			/*!
			*	\brief	Gets the width of this texture.
			*	\return Width of the texture.
			*/
			virtual unsigned int getWidth() = 0;

			/*!
			*	\brief	Gets the height of this texture.
			*	\return Height of the texture.
			*/
			virtual unsigned int getHeight() = 0;

			/*!
			*	\brief	Binds this texture with the given unit number
			*			ready for use.
			*/
			virtual void bind(unsigned int unit) const = 0;
	};
}