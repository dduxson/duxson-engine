/*!********************************************************************
* File:	IRenderVisualEntityVisitor.h
*
* \brief	Interface used to render all visual components of entities
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
	enum RenderOrder;
	class IVisualEngine;

	class IRenderVisualEntityVisitor : public IEntityVisitor
	{
		public:
			typedef std::shared_ptr<IRenderVisualEntityVisitor> SPtr;

			IRenderVisualEntityVisitor() {}
			virtual ~IRenderVisualEntityVisitor() {}

			virtual void setVisualEngine(std::shared_ptr<IVisualEngine> visualEngine) = 0;
			virtual void setRenderPass(RenderOrder renderPass) = 0;
	};
}