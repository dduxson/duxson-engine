#include "include\SphereGeometry.h"

namespace DE
{
	SphereGeometry::SphereGeometry(float radius, const glm::vec4& colour)
		: Geometry()
	{
		setGeometryType(Geometry::eTriangleStripGeometry);

		unsigned int index = 0;

		for (float phi = -90.0f; phi <= 90.0f; phi += 10.0f)
		{
			float phiRad = glm::radians(phi);
			float phiRad10 = glm::radians(phi + 10.0f);

			for (float theta = -180.0f; theta <= 180.0f; theta += 10.0f)
			{
				float thetaRad = glm::radians(theta);
				m_vertices.push_back( glm::vec3( radius * sinf(thetaRad) * cos(phiRad),
											     radius * cosf(thetaRad) * cos(phiRad),
											     radius * sinf(phiRad) ) );
				m_vertices.push_back( glm::vec3( radius * sinf(thetaRad) * cos(phiRad10),
											     radius * cosf(thetaRad) * cos(phiRad10),
											     radius * sinf(phiRad10) ) );
				m_colours.push_back(colour);
				m_colours.push_back(colour);

				m_indicies.push_back(index);
				m_indicies.push_back(index + 1);
				index += 2;
			}
		}

		for (unsigned int i = 0; i < m_vertices.size(); ++i)
			m_normals.push_back(glm::normalize(m_vertices[i]));
	}
}
