#include "EntityFollow.h"
#include "../DuxsonEngine/include/IEntity.h"
#include <iostream>

EntityFollow::EntityFollow(DE::Entity::SPtr entity)
	: m_entity(entity)
	, m_posScale(1.0f, 1.0f, 1.0f)
	, m_rotScale(1.0f, 1.0f, 1.0f)
	, m_posOffset(0.0f, 0.0f, 0.0f)
	, m_rotOffset(0.0f, 0.0f, 0.0f)
	, m_twoD(false)
{

}

EntityFollow::~EntityFollow()
{

}

void EntityFollow::setPositionScalar(const glm::vec3& scalar)
{
	m_posScale = scalar;
}

void EntityFollow::setRotationScalar(const glm::vec3& scalar)
{
	m_rotScale = scalar;
}

void EntityFollow::setPositionOffset(const glm::vec3& offset)
{
	m_posOffset = offset;
}

void EntityFollow::setRotationOffset(const glm::vec3& offset)
{
	m_rotOffset = offset;
}

void EntityFollow::setTwoD(bool twoD)
{
	m_twoD = twoD;
}

void EntityFollow::update(DE::IVisualEngine::SPtr visualEngine, float dtSecs)
{
	if (m_entity)
	{
		glm::vec3 translation = m_entity->getTransform().getTrans();
		glm::quat rotation = m_entity->getTransform().getRot();
		glm::vec3 eulerRot = glm::eulerAngles(rotation);

		if (m_twoD)
		{
			translation.x = translation.x * m_posScale.x + m_posOffset.x;
			translation.y = -translation.z * m_posScale.y + m_posOffset.y;
			translation.z = m_posOffset.z;

			float eulerRotZ = eulerRot.z;

			eulerRot.x = eulerRotZ * m_rotScale.x + m_rotOffset.x;
			eulerRot.z = eulerRot.y *m_rotScale.z + m_rotOffset.z;
			eulerRot.y = m_rotOffset.y;
		}
		else
		{
			translation.x = translation.x * m_posScale.x + m_posOffset.x;
			translation.y = translation.y * m_posScale.y + m_posOffset.y;
			translation.z = translation.z * m_posScale.z + m_posOffset.z;

			eulerRot.x = eulerRot.x * m_rotScale.x + m_rotOffset.x;
			eulerRot.y = eulerRot.y * m_rotScale.y + m_rotOffset.y;
			eulerRot.z = eulerRot.z * m_rotScale.z + m_rotOffset.z;
		}

		rotation = glm::angleAxis(eulerRot.x, glm::vec3(1.0, 0.0, 0.0)) * glm::angleAxis(eulerRot.y, glm::vec3(0.0, 1.0, 0.0)) * glm::angleAxis(eulerRot.z, glm::vec3(0.0, 0.0, 1.0));

		DE::IEntity::SPtr parent = m_parent.lock();
		
		if (parent != nullptr)
		{
			parent->setTrans(translation);
			parent->setRot(rotation);
		}
	}
}

void EntityFollow::render(DE::IVisualEngine::SPtr visualEngine) const
{

}