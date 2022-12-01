/*!********************************************************************
* File:	IUpdateVisualEntityVisitor.h
*
* \brief	Interface used to updated all visual components of entities
*			in the entity scene graph.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include "IEntityVisitor.h"

namespace DE
{
	class IVisualEngine;

	class IUpdateVisualEntityVisitor : public IEntityVisitor
	{
		public:
			typedef std::shared_ptr<IUpdateVisualEntityVisitor> SPtr;

			IUpdateVisualEntityVisitor() {}
			virtual ~IUpdateVisualEntityVisitor() {}

			virtual void setVisualEngine(std::shared_ptr<IVisualEngine> visualEngine) = 0;
			virtual void setDeltaSecs(float dtSecs) = 0;
	};
}