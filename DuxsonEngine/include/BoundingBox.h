/*!********************************************************************
* File:	BoundingBox.h
*
* \brief	Class that represents a bounding box in the Duxson
*			Engine
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once
#include <glm/glm.hpp>

namespace DE
{
	class BoundingBox
	{
		public:
			BoundingBox();
			BoundingBox(const glm::vec3& min, const glm::vec3& max);
			virtual ~BoundingBox();

			void setMin(const glm::vec3& min);
			void setMax(const glm::vec3& max);
			glm::vec3 getMin() const;
			glm::vec3 getMax() const;

			float getWidth() const;
			float getLength() const;
			float getHeight() const;
			glm::vec3 getCenter() const;

			void extendBy(const glm::vec3& v);
			void extendBy(const BoundingBox& bb);

			bool containsPoint(const glm::vec3& point) const;

			bool checkAABoundingBoxesIntersect(const BoundingBox& bbOther) const;

		private:
			glm::vec3 m_min;
			glm::vec3 m_max;
	};
}
