/*!********************************************************************
* File:	UpdateVisualEntityVisitor.h
*
* \brief	Class used to updated all visual components of entities
*			in the entity scene graph.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include "IUpdateVisualEntityVisitor.h"

namespace DE
{
	class IVisualEngine;

	class UpdateVisualEntityVisitor : public IUpdateVisualEntityVisitor
	{

		public:
			UpdateVisualEntityVisitor();
			virtual ~UpdateVisualEntityVisitor();

			void setDeltaSecs(float dtSecs);
			void setVisualEngine(std::shared_ptr<IVisualEngine> visualEngine);
			virtual void apply(std::shared_ptr<IEntity> entity);

		private:
			std::weak_ptr<IVisualEngine>  m_visualEngine;
			float m_dtSecs;
	};
}