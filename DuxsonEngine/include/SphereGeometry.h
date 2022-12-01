#pragma once

#include "Geometry.h"

namespace DE
{
	class SphereGeometry : public Geometry
	{
		public:
			SphereGeometry(float radius = 0.5f, const glm::vec4& colour = glm::vec4(1,1,1,1));
	};
}