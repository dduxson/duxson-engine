#include "./include/Geometry.h"

namespace DE {
	Geometry::Geometry(const std::vector<unsigned int>& indicies, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& texCoords,
		const std::vector<glm::vec3>& normals, const std::vector<glm::vec3>& tangents, const std::vector<glm::vec4>& colours)
		: m_indicies(indicies)
		, m_vertices(vertices)
		, m_texCoords(texCoords)
		, m_normals(normals)
		, m_tangents(tangents)
		, m_colours(colours)
		, m_type(eTriangleGeometry)
	{

	}

	Geometry::Geometry(const Geometry& geometry)
	{
		const std::vector<unsigned int>& indicies = geometry.getIndexArray();
		const std::vector<glm::vec3>& vertices = geometry.getVertexArray();
		const std::vector<glm::vec2>& texCoords = geometry.getTexCoordArray();
		const std::vector<glm::vec3>& normals = geometry.getNormalArray();
		const std::vector<glm::vec3>& tangents = geometry.getTangentArray();
		const std::vector<glm::vec4>& colours = geometry.getColourArray();

		for (unsigned int i = 0; i < indicies.size(); ++i)
			m_indicies.push_back(indicies[i]);

		for (unsigned int i = 0; i < vertices.size(); ++i)
			m_vertices.push_back(vertices[i]);

		for (unsigned int i = 0; i < texCoords.size(); ++i)
			m_texCoords.push_back(texCoords[i]);

		for (unsigned int i = 0; i < normals.size(); ++i)
			m_normals.push_back(normals[i]);

		for (unsigned int i = 0; i < tangents.size(); ++i)
			m_tangents.push_back(tangents[i]);

		for (unsigned int i = 0; i < colours.size(); ++i)
			m_colours.push_back(colours[i]);

		m_type = geometry.getGeometryType();
	}

	bool Geometry::isValid() const
	{
		if (!(m_vertices.size() > 0 && m_indicies.size() > 0))
			return false;

		if (m_texCoords.size() > 0 && m_texCoords.size() != m_vertices.size())
			return false;

		if (m_normals.size() > 0 && m_normals.size() != m_vertices.size())
			return false;

		if (m_tangents.size() > 0 && m_tangents.size() != m_vertices.size())
			return false;

		if (m_colours.size() > 0 && m_colours.size() != m_vertices.size())
			return false;

		return true;
	}

	bool Geometry::finalizeGeom()
	{
		if (m_normals.size() == 0)
			calcNormals();

		if (m_tangents.size() == 0)
			calcTangents();

		if (isValid())
			return true;

		return false;
	}

	Geometry::Geometry()
		: m_type(Geometry::eTriangleGeometry)
	{
	}

	void Geometry::calcNormals()
	{
		m_normals.clear();
		m_normals.reserve(m_vertices.size());

		for (unsigned int i = 0; i < m_vertices.size(); i++)
			m_normals.push_back(glm::vec3(0, 0, 0));

		for (unsigned int i = 0; i < m_indicies.size(); i += 3)
		{
			int i0 = m_indicies[i];
			int i1 = m_indicies[i + 1];
			int i2 = m_indicies[i + 2];

			glm::vec3 v1 = m_vertices[i1] - m_vertices[i0];
			glm::vec3 v2 = m_vertices[i2] - m_vertices[i0];

			glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

			m_normals[i0] = m_normals[i0] + normal;
			m_normals[i1] = m_normals[i1] + normal;
			m_normals[i2] = m_normals[i2] + normal;
		}

		for (unsigned int i = 0; i < m_normals.size(); i++)
			m_normals[i] = glm::normalize(m_normals[i]);
	}

	void Geometry::calcTangents()
	{
		if (m_texCoords.size() == m_vertices.size())
		{
			m_tangents.clear();
			m_tangents.reserve(m_vertices.size());

			for (unsigned int i = 0; i < m_vertices.size(); i++)
				m_tangents.push_back(glm::vec3(0, 0, 0));

			for (unsigned int i = 0; i < m_indicies.size(); i += 3)
			{
				int i0 = m_indicies[i];
				int i1 = m_indicies[i + 1];
				int i2 = m_indicies[i + 2];

				glm::vec3 edge1 = m_vertices[i1] - m_vertices[i0];
				glm::vec3 edge2 = m_vertices[i2] - m_vertices[i0];

				float deltaU1 = m_texCoords[i1].x - m_texCoords[i0].x;
				float deltaU2 = m_texCoords[i2].x - m_texCoords[i0].x;
				float deltaV1 = m_texCoords[i1].y - m_texCoords[i0].y;
				float deltaV2 = m_texCoords[i2].y - m_texCoords[i0].y;

				float dividend = (deltaU1 * deltaV2 - deltaU2 * deltaV1);
				float f = dividend == 0.0f ? 0.0f : 1.0f / dividend;

				glm::vec3 tangent = glm::vec3(0, 0, 0);

				tangent.x = (f * (deltaV2 * edge1.x - deltaV1 * edge2.x));
				tangent.y = (f * (deltaV2 * edge1.y - deltaV1 * edge2.y));
				tangent.z = (f * (deltaV2 * edge1.z - deltaV1 * edge2.z));

				m_tangents[i0] += tangent;
				m_tangents[i1] += tangent;
				m_tangents[i2] += tangent;
			}

			for (unsigned int i = 0; i < m_tangents.size(); i++)
			{
				if ((m_tangents[i].x != 0.0f) && (m_tangents[i].y != 0.0f) && (m_tangents[i].z != 0.0f))
					m_tangents[i] = glm::normalize(m_tangents[i]);
			}
		}
	}

	const std::vector<unsigned int>& Geometry::getIndexArray() const
	{
		return m_indicies;
	}

	const std::vector<glm::vec3>&	Geometry::getVertexArray() const
	{
		return m_vertices;
	}

	const std::vector<glm::vec2>&	Geometry::getTexCoordArray() const
	{
		return m_texCoords;
	}

	const std::vector<glm::vec3>&	Geometry::getNormalArray() const
	{
		return m_normals;
	}

	const std::vector<glm::vec3>&	Geometry::getTangentArray() const
	{
		return m_tangents;
	}

	const std::vector<glm::vec4>&	Geometry::getColourArray() const
	{
		return m_colours;
	}

	Geometry::GeometryType Geometry::getGeometryType() const
	{
		return m_type;
	}

	void Geometry::setGeometryType(GeometryType type)
	{
		m_type = type;
	}
}