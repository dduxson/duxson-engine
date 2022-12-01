/*!********************************************************************
* File:	IEntityVisitor.h
*
* \brief	Interface that represents a basic entity visitor in the
*			Duxson Engine
* \details	Entities in a graph can be all acted upon by a visitor.
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
	class IEntity;

	class IEntityVisitor : public std::enable_shared_from_this<IEntityVisitor>
	{
		public:
			typedef std::shared_ptr<IEntityVisitor> SPtr;

			IEntityVisitor() {};
			virtual ~IEntityVisitor() {};

			virtual void apply(std::shared_ptr<IEntity> entity) = 0;
	};
}