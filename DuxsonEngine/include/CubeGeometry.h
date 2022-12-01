#pragma once

#include "Geometry.h"

namespace DE
{
	class CubeGeometry : public Geometry
	{
		public:
			CubeGeometry(const std::vector<glm::vec4>& colours = std::vector<glm::vec4>());
	};
}