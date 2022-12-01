/*!********************************************************************
* File:	IMesh.h
*
* \brief	Interface that hold the geometry of objects and the OpenGL
*			specifics required to render the geometry.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once
#include "BoundingBox.h"
#include <memory>

namespace DE
{
	class IMesh
	{
		public:
			typedef std::shared_ptr<IMesh> SPtr;
			typedef std::weak_ptr<IMesh> WPtr;

			IMesh() {}
			virtual ~IMesh() {}

			/*!
			*	\brief	Does some basic size checking to see if the geometry looks
			*			valid.
			*	\return True if looks valid, false otherwise.
			*/
			virtual bool isValid() = 0;

			/*!
			*	\brief	Draws the geometry to screen.
			*/
			virtual void draw() const = 0;

			/*!
			*	\brief	Gets the bounding box for this mesh asset.
			*	\return Bounding box for this mesh asset.
			*/
			virtual BoundingBox getBoundingBox() const = 0;
	};
}