/*!********************************************************************
* File:	Entity.h
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

#include "IEntity.h"

namespace DE
{
	class Entity : public IEntity
	{
		public:
			Entity(bool absoluteCoords = false, const glm::vec3& trans = glm::vec3(0, 0, 0), const glm::quat& rot = glm::quat(), const glm::vec3& scale = glm::vec3(1, 1, 1));
			virtual ~Entity();

			bool isRoot();
			IEntity::SPtr getParent();
			void setParent(IEntity::SPtr parent);
			void setAbsoluteCoords(bool absolute);

			void addChild(IEntity::SPtr child);
			void removeChild(IEntity::SPtr child);
			unsigned int getNumOfChildren(bool recursive);
			std::vector<IEntity::SPtr> getChildren();

			void addComponent(IEntityComponent::SPtr component);
			std::vector<IEntityComponent::SPtr> getComponents();

			void traverse(IEntityVisitor::SPtr entityVisitor) const;

			const Transform& getTransform();
			const Transform& getWorldTransform();

			void setTrans(const glm::vec3& trans);
			void setRot(const glm::quat& rot);
			void setScale(const glm::vec3& scale);
			void setWorldTrans(const glm::vec3& trans);
			void setWorldRot(const glm::quat& rot);
			void setWorldScale(const glm::vec3& scale);

			void applyParentDTrans(const glm::vec3& dTrans);
			void applyParentDRot(const glm::quat& dRot);
			void applyParentDScale(const glm::vec3& dScale);

			BoundingBox getBoundingBox();

		private:
			IEntity::WPtr						m_parent;
			std::vector<IEntity::SPtr>			m_children;
			std::vector<IEntityComponent::SPtr>	m_components;

			bool								m_absoluteCoords;
			Transform							m_transform;
			Transform							m_worldTransform;
			BoundingBox							m_boundingBox;
			bool								m_recomputeBoundingBox;
	};
}
