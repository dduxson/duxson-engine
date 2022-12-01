#include "include\CubeGeometry.h"

namespace DE
{
	CubeGeometry::CubeGeometry(const std::vector<glm::vec4>& colours)
		: Geometry()
	{
		m_indicies = { 0, 1, 2, 0, 2, 3,			//front
						6, 5, 4, 7, 6, 4,			//right
						10, 9, 8, 11, 10, 8,		//back
						12, 13, 14, 12, 14, 15,		//left
						18, 17, 16, 19, 18, 16,		//upper
						20, 21, 22, 20, 22, 23 };	//bottom

		//front
		m_vertices.push_back(glm::vec3(-0.5, -0.5, 0.5));
		m_vertices.push_back(glm::vec3(0.5, -0.5, 0.5));
		m_vertices.push_back(glm::vec3(0.5, 0.5, 0.5));
		m_vertices.push_back(glm::vec3(-0.5, 0.5, 0.5));

		//right
		m_vertices.push_back(glm::vec3(0.5, 0.5, 0.5));
		m_vertices.push_back(glm::vec3(0.5, 0.5, -0.5));
		m_vertices.push_back(glm::vec3(0.5, -0.5, -0.5));
		m_vertices.push_back(glm::vec3(0.5, -0.5, 0.5));

		//back
		m_vertices.push_back(glm::vec3(-0.5, -0.5, -0.5));
		m_vertices.push_back(glm::vec3(0.5, -0.5, -0.5));
		m_vertices.push_back(glm::vec3(0.5, 0.5, -0.5));
		m_vertices.push_back(glm::vec3(-0.5, 0.5, -0.5));

		//left
		m_vertices.push_back(glm::vec3(-0.5, -0.5, -0.5));
		m_vertices.push_back(glm::vec3(-0.5, -0.5, 0.5));
		m_vertices.push_back(glm::vec3(-0.5, 0.5, 0.5));
		m_vertices.push_back(glm::vec3(-0.5, 0.5, -0.5));

		//upper
		m_vertices.push_back(glm::vec3(0.5, 0.5, 0.5));
		m_vertices.push_back(glm::vec3(-0.5, 0.5, 0.5));
		m_vertices.push_back(glm::vec3(-0.5, 0.5, -0.5));
		m_vertices.push_back(glm::vec3(0.5, 0.5, -0.5));

		//bottom
		m_vertices.push_back(glm::vec3(-0.5, -0.5, -0.5));
		m_vertices.push_back(glm::vec3(0.5, -0.5, -0.5));
		m_vertices.push_back(glm::vec3(0.5, -0.5, 0.5));
		m_vertices.push_back(glm::vec3(-0.5, -0.5, 0.5));

		m_colours = colours;

		finalizeGeom();
	}
}
