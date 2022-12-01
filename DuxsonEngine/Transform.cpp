#include "./include/Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace DE
{
	Transform::Transform(const glm::vec3& trans, const glm::quat& rot, const glm::vec3& scale)
		: m_trans(trans)
		, m_rot(rot)
		, m_scale(scale)
	{

	}

	glm::mat4 Transform::getTransformation() const
	{
		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;

		translationMatrix = glm::translate(translationMatrix, m_trans);
		scaleMatrix = glm::scale(scaleMatrix, m_scale);
		rotationMatrix = glm::mat4_cast(m_rot);

		return (translationMatrix * rotationMatrix  * scaleMatrix);
	}

	glm::vec3 Transform::getTrans() const
	{
		return m_trans;
	}

	glm::quat Transform::getRot() const
	{
		return m_rot;
	}

	glm::vec3 Transform::getScale() const
	{
		return m_scale;
	}

	glm::vec3 Transform::getForwardDir() const
	{
		glm::mat4 transformation = glm::mat4_cast(getRot());
		glm::vec4 forwardDir = transformation * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

		return glm::vec3(forwardDir);
	}

	glm::vec3 Transform::getUpDir() const
	{
		glm::mat4 transformation = glm::mat4_cast(getRot());
		glm::vec4 upDir = transformation * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

		return glm::vec3(upDir);
	}

	glm::vec3 Transform::getRightDir() const
	{
		glm::mat4 transformation = glm::mat4_cast(getRot());
		glm::vec4 rightDir = transformation * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);

		return glm::vec3(rightDir);
	}

	void Transform::setTrans(const glm::vec3& trans)
	{
		m_trans = trans;
	}

	void Transform::setRot(const glm::quat& rot)
	{
		m_rot = glm::normalize(rot);
	}

	void Transform::setScale(const glm::vec3& scale)
	{
		m_scale = scale;
	}

	glm::quat Transform::lookAt(const glm::vec3& eye, const glm::vec3& look, const glm::vec3& up) const
	{
		glm::mat4 viewMat = glm::lookAt(eye, look, up);
		glm::mat4 camMat = glm::inverse(viewMat);
		glm::quat rot = glm::quat_cast(camMat);

		return rot;
	}
}