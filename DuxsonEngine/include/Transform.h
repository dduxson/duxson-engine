/*!********************************************************************
* File:	Transform.h
*
* \brief	Class that represents a transform for a entity.
* \details This class is helpful due to the fact we store translation,
*			rotation and scale separatly so can easily get and set them
*			individually. It also enables different pieces of code to
*			to modify the parameters again and again without worrying
*			about the order of matrix multiplication.
*			We also attempt to make it much harder to get into the
*			problem of gimbal lock.
*
* \author	David Duxson
*
* \date	19/12/2015
*
**********************************************************************/
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace DE
{
	class Transform
	{
		public:
			Transform(const glm::vec3& trans = glm::vec3(0, 0, 0), const glm::quat& rot = glm::quat(0, 0, 0, 1), const glm::vec3& scale = glm::vec3(1, 1, 1));

			glm::mat4 getTransformation() const;

			glm::vec3 getTrans() const;
			glm::quat getRot() const;
			glm::vec3 getScale() const;

			glm::vec3 getForwardDir() const;
			glm::vec3 getUpDir() const;
			glm::vec3 getRightDir() const;

			void setTrans(const glm::vec3& trans);
			void setRot(const glm::quat& rot);
			void setScale(const glm::vec3& scale);

			glm::quat lookAt(const glm::vec3& eye, const glm::vec3& look, const glm::vec3& up) const;

		private:
			glm::vec3 m_trans;
			glm::quat m_rot;
			glm::vec3 m_scale;
	};
}