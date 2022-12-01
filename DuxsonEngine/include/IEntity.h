/*!********************************************************************
* File:	IEntity.h
*
* \brief	Interface that represents a basic entity in the Duxson
*			Engine
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "IEntityComponent.h"
#include "IEntityVisitor.h"
#include "Transform.h"
#include "BoundingBox.h"

namespace DE
{
	class IEntity : public std::enable_shared_from_this<IEntity>
	{
		public:
			typedef std::shared_ptr<IEntity> SPtr;
			typedef std::weak_ptr<IEntity> WPtr;

			IEntity() {}
			virtual ~IEntity() {}

			virtual bool isRoot() = 0;
			virtual IEntity::SPtr getParent() = 0;
			virtual void setParent(IEntity::SPtr parent) = 0;
			virtual void setAbsoluteCoords(bool absolute) = 0;

			virtual void addChild(IEntity::SPtr child) = 0;
			virtual void removeChild(IEntity::SPtr child) = 0;
			virtual unsigned int getNumOfChildren(bool recursive) = 0;
			virtual std::vector<IEntity::SPtr> getChildren() = 0;

			virtual void addComponent(IEntityComponent::SPtr component) = 0;
			virtual std::vector<IEntityComponent::SPtr> getComponents() = 0;

			virtual void traverse(IEntityVisitor::SPtr entityVisitor) const = 0;

			virtual const Transform& getTransform() = 0;
			virtual const Transform& getWorldTransform() = 0;
			
			virtual void setTrans(const glm::vec3& trans) = 0;
			virtual void setRot(const glm::quat& rot) = 0;
			virtual void setScale(const glm::vec3& scale) = 0;
			virtual void setWorldTrans(const glm::vec3& trans) = 0;
			virtual void setWorldRot(const glm::quat& rot) = 0;
			virtual void setWorldScale(const glm::vec3& scale) = 0;

			virtual void applyParentDTrans(const glm::vec3& dTrans) = 0;
			virtual void applyParentDRot(const glm::quat& dRot) = 0;
			virtual void applyParentDScale(const glm::vec3& dScale) = 0;

			virtual BoundingBox getBoundingBox() = 0;
	};
}
