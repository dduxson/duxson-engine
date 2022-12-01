#include "./Include/BoundingBox.h"

namespace DE
{
	BoundingBox::BoundingBox()
		: m_min(0.0f)
		, m_max(0.0f)
	{

	}

	BoundingBox::BoundingBox(const glm::vec3& min, const glm::vec3& max)
		: m_min(min)
		, m_max(max)
	{

	}

	BoundingBox::~BoundingBox()
	{

	}

	void BoundingBox::setMin(const glm::vec3& min)
	{
		m_min = min;
	}

	void BoundingBox::setMax(const glm::vec3& max)
	{
		m_max = max;
	}

	glm::vec3 BoundingBox::getMin() const
	{
		return m_min;
	}

	glm::vec3 BoundingBox::getMax() const
	{
		return m_max;
	}

	void BoundingBox::extendBy(const glm::vec3& v)
	{
		if (v.x > m_max.x)
			m_max.x = v.x;
		if (v.x < m_min.x)
			m_min.x = v.x;

		if (v.y > m_max.y)
			m_max.y = v.y;
		if (v.y < m_min.y)
			m_min.y = v.y;

		if (v.z > m_max.z)
			m_max.z = v.z;
		if (v.z < m_min.z)
			m_min.z = v.z;
	}

	void BoundingBox::extendBy(const BoundingBox& bb)
	{
		if (bb.getMax().x > m_max.x)
			m_max.x = bb.getMax().x;
		if (bb.getMin().x < m_min.x)
			m_min.x = bb.getMin().x;

		if (bb.getMax().y > m_max.y)
			m_max.y = bb.getMax().y;
		if (bb.getMin().y < m_min.y)
			m_min.y = bb.getMin().y;

		if (bb.getMax().z > m_max.z)
			m_max.z = bb.getMax().z;
		if (bb.getMin().z < m_min.z)
			m_min.z = bb.getMin().z;
	}

	bool BoundingBox::containsPoint(const glm::vec3& point) const
	{
		return (point.x >= m_min.x && point.y >= m_min.y && point.z >= m_min.z &&
			point.x <= m_max.x && point.y <= m_max.y && point.z <= m_max.z);
	}

	bool BoundingBox::checkAABoundingBoxesIntersect(const BoundingBox& bbOther) const
	{
		if (getMax().x < bbOther.getMin().x)
			return false; // a is left of b
		if (getMin().x > bbOther.getMax().x)
			return false; // a is right of b
		if (getMax().y < bbOther.getMin().y)
			return false; // a is above b
		if (getMin().y > bbOther.getMax().y)
			return false; // a is below b
		if (getMax().z < bbOther.getMin().z)
			return false; // a is in front b
		if (getMin().z > bbOther.getMax().z)
			return false; // a is behind b

		return true;
	}

	float BoundingBox::getWidth() const
	{
		return fabs(m_max.x - m_min.x);
	}

	float BoundingBox::getLength() const
	{
		return fabs(m_max.z - m_min.z);
	}

	float BoundingBox::getHeight() const
	{
		return fabs(m_max.y - m_min.y);
	}

	glm::vec3 BoundingBox::getCenter() const
	{
		return glm::vec3(m_min.x + (0.5f*getWidth()), m_min.y + (0.5f*getHeight()), m_min.z + (0.5f*getLength()));
	}
}