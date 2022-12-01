#include "./include/Entity.h"

namespace DE
{
	Entity::Entity(bool absoluteCoords, const glm::vec3 & trans, const glm::quat & rot, const glm::vec3 & scale)
		: m_absoluteCoords(absoluteCoords)
		, m_recomputeBoundingBox(true)
	{
		m_transform = Transform(trans, rot, scale);
		m_worldTransform = Transform(trans, rot, scale);
	}

	Entity::~Entity()
	{
		bool test = true;
	}

	bool Entity::isRoot()
	{
		if (m_parent.lock() == nullptr)
			return true;

		return false;
	}

	IEntity::SPtr Entity::getParent()
	{
		return m_parent.lock();
	}

	void Entity::setParent(IEntity::SPtr parent)
	{
		if (m_parent.lock() != nullptr)
			m_parent.lock()->removeChild(shared_from_this());

		m_parent = parent;

		setAbsoluteCoords(m_absoluteCoords);

		m_recomputeBoundingBox = true;

		parent->addChild(shared_from_this());
	}

	void Entity::addChild(IEntity::SPtr child)
	{
		if (child == nullptr)
			return;

		if(child->getParent() != shared_from_this())
			child->setParent(shared_from_this());

		
		m_children.push_back(child);
	}

	void Entity::removeChild(IEntity::SPtr child)
	{
		if ((child == nullptr) || (m_children.empty()))
			return;

		//Loop through children and find this child.
		for (unsigned int i = 0; i < m_children.size(); ++i)
		{
			if (m_children[i] == child)
			{
				m_children.erase(m_children.begin() + i);

				//Set world transform to equal local of child
				child->setWorldTrans(child->getTransform().getTrans());
				child->setWorldRot(child->getTransform().getRot());
				child->setWorldScale(child->getTransform().getScale());

				m_recomputeBoundingBox = true;
				break;
			}
		}
	}

	unsigned int Entity::getNumOfChildren(bool recursive)
	{
		if (!recursive)
		{
			return m_children.size();
		}
		else
		{
			unsigned int num = m_children.size();
			for (unsigned int i = 0; i < m_children.size(); ++i)
				num += m_children[i]->getNumOfChildren(true);

			return(num);
		}
	}

	std::vector<IEntity::SPtr> Entity::getChildren()
	{
		return m_children;
	}

	void Entity::addComponent(IEntityComponent::SPtr component)
	{
		m_components.push_back(component);
		component->setParent(shared_from_this());
	}

	std::vector<IEntityComponent::SPtr> Entity::getComponents()
	{
		return m_components;
	}

	BoundingBox Entity::getBoundingBox()
	{
		if (m_recomputeBoundingBox)
		{
			m_boundingBox = BoundingBox();

			for (unsigned int i = 0; i < m_components.size(); ++i)
				m_boundingBox.extendBy(m_components[i]->boundingBox());

			m_recomputeBoundingBox = false;
		}

		return m_boundingBox;
	}

	void Entity::traverse(IEntityVisitor::SPtr entityVisitor) const
	{
		if (m_children.empty())
			return;

		for (unsigned int i = 0; i < m_children.size(); ++i)
		{
			if (m_children[i])
				entityVisitor->apply(m_children[i]);
		}
	}

	const Transform& Entity::getTransform()
	{
		return m_transform;
	}

	const Transform& Entity::getWorldTransform()
	{
		return m_worldTransform;
	}

	void Entity::setTrans(const glm::vec3& trans)
	{
		glm::vec3 delta = trans - m_transform.getTrans();
		m_transform.setTrans(trans);
		m_worldTransform.setTrans(m_worldTransform.getTrans() + delta);

		for (unsigned int i = 0; i < m_children.size(); ++i)
			m_children[i]->applyParentDTrans(delta);
	}

	void Entity::setRot(const glm::quat& rot)
	{
		glm::quat delta = glm::normalize(glm::inverse(m_transform.getRot()) * rot);

		m_transform.setRot(rot);
		m_worldTransform.setRot(m_worldTransform.getRot() * delta);

		for (unsigned int i = 0; i < m_children.size(); ++i)
			m_children[i]->applyParentDRot(delta);
	}

	void Entity::setScale(const glm::vec3& scale)
	{
		glm::vec3 delta = scale - m_transform.getScale();
		m_transform.setScale(scale);
		m_worldTransform.setScale(m_worldTransform.getScale() + delta);

		for (unsigned int i = 0; i < m_children.size(); ++i)
			m_children[i]->applyParentDScale(delta);
	}

	void Entity::setWorldTrans(const glm::vec3& trans)
	{
		glm::vec3 delta = trans - m_worldTransform.getTrans();
		m_worldTransform.setTrans(trans);
		m_transform.setTrans(m_transform.getTrans() + delta);

		for (unsigned int i = 0; i < m_children.size(); ++i)
			m_children[i]->applyParentDTrans(delta);
	}

	void Entity::setWorldRot(const glm::quat& rot)
	{
		glm::quat delta = glm::normalize(glm::inverse(m_worldTransform.getRot()) * rot);
		m_worldTransform.setRot(rot);
		m_transform.setRot(m_transform.getRot() * delta);

		for (unsigned int i = 0; i < m_children.size(); ++i)
			m_children[i]->applyParentDRot(delta);
	}

	void Entity::setWorldScale(const glm::vec3& scale)
	{
		glm::vec3 delta = scale - m_worldTransform.getScale();
		m_worldTransform.setScale(scale);
		m_transform.setScale(m_transform.getScale() + delta);

		for (unsigned int i = 0; i < m_children.size(); ++i)
			m_children[i]->applyParentDScale(delta);
	}

	void Entity::applyParentDTrans(const glm::vec3& dTrans)
	{
		if (!m_absoluteCoords)
		{
			m_worldTransform.setTrans(m_worldTransform.getTrans() + dTrans);

			for (unsigned int i = 0; i < m_children.size(); ++i)
				m_children[i]->applyParentDTrans(dTrans);
		}
	}

	void Entity::applyParentDRot(const glm::quat& dRot)
	{
		if (!m_absoluteCoords)
		{
			m_worldTransform.setRot(m_worldTransform.getRot() * glm::normalize(dRot));

			for (unsigned int i = 0; i < m_children.size(); ++i)
				m_children[i]->applyParentDRot(dRot);
		}
	}

	void Entity::applyParentDScale(const glm::vec3& dScale)
	{
		if (!m_absoluteCoords)
		{
			m_worldTransform.setScale(m_worldTransform.getScale() + dScale);

			for (unsigned int i = 0; i < m_children.size(); ++i)
				m_children[i]->applyParentDScale(dScale);
		}
	}

	void Entity::setAbsoluteCoords(bool absolute)
	{
		m_absoluteCoords = absolute;

		if (m_absoluteCoords || (m_parent.lock() == nullptr))
		{
			m_worldTransform = m_transform;
		}
		else
		{
			auto m_parent_sptr = m_parent.lock();
			setWorldTrans(m_parent_sptr->getWorldTransform().getTrans() + m_transform.getTrans());
			setWorldRot(m_transform.getRot() * m_parent_sptr->getWorldTransform().getRot());
			setWorldScale(m_parent_sptr->getWorldTransform().getScale() * m_transform.getScale());
		}
	}
}