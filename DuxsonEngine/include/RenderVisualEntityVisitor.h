/*!********************************************************************
* File:	RenderVisualEntityVisitor.h
*
* \brief	Class used to render all visual components of entities
*			in the entity scene graph.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include "IRenderVisualEntityVisitor.h"

namespace DE
{
	class IVisualEngine;
	enum RenderOrder;

	class RenderVisualEntityVisitor : public IRenderVisualEntityVisitor
	{
		public:
			RenderVisualEntityVisitor();
			virtual ~RenderVisualEntityVisitor();

			void setRenderPass(RenderOrder renderPass);
			void setVisualEngine(std::shared_ptr<IVisualEngine> visualEngine);

			virtual void apply(std::shared_ptr<IEntity> entity);

		private:
			std::weak_ptr<IVisualEngine>  m_visualEngine;
			RenderOrder	  m_renderPass;

			RenderOrder	  m_currentRenderOrder; ///< The last scene render order when traversing the scene graph (eRender by default)
	};
}