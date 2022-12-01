#pragma once
#include <GL/glew.h>
#include "./Include/Mesh.h"
#include "./Include/Logger.h"

namespace DE
{
	std::map<std::string, MeshAsset::WPtr> Mesh::ms_asset_map;

	Mesh::Mesh(const std::string& name, Geometry::SPtr geom)
		: m_name(name)
	{
		std::map<std::string, MeshAsset::WPtr>::const_iterator it = ms_asset_map.find(name);

		if (it != ms_asset_map.end() && (!it->second.expired()))
		{
			Logger::Instance()->writeToLogFile(Logger::eLogError, "Failed to create mesh asset with name: %s as one with this name already exists.", m_name.c_str());
		}
		else
		{
			m_asset = std::make_shared<MeshAsset>(geom);
			ms_asset_map[m_name] = m_asset;

			Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Created mesh asset with name: %s.", m_name.c_str());
		}
	}

	Mesh::Mesh(const Mesh& mesh)
		: m_name(mesh.m_name),
		m_asset(mesh.m_asset)
	{

	}

	Mesh::~Mesh()
	{

	}

	void Mesh::draw() const
	{
		if (m_asset)
			m_asset->draw();
	}

	bool Mesh::isValid()
	{
		if (!m_asset)
			return false;

		return m_asset->isValid();
	}

	BoundingBox Mesh::getBoundingBox() const
	{
		if (!m_asset)
			return BoundingBox();

		return m_asset->getBoundingBox();
	}

	MeshAsset::MeshAsset(Geometry::SPtr geometry)
		: m_geometry(geometry)
	{
		setupOpenGLData();
		computeBoundingBox();
	}

	MeshAsset::~MeshAsset()
	{
		clearGeometry();
		Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Deleted mesh asset.");
	}

	bool MeshAsset::isValid()
	{
		if (m_geometry == nullptr)
			return false;

		return m_geometry->isValid();
	}

	void MeshAsset::clearGeometry()
	{
		if (m_vbos.size() > 0)
			glDeleteBuffers(m_vbos.size(), &m_vbos[0]);

		glDeleteVertexArrays(1, &m_vao);

		m_vbos.clear();
	}

	bool MeshAsset::setupOpenGLData()
	{
		if (m_geometry == nullptr)
			return false;

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		//Find out how many buffers we require (1 at least: positions)
		m_vbos.push_back(0);
		if (m_geometry->getIndexArray().size() > 0)
			m_vbos.push_back(0);
		if (m_geometry->getTexCoordArray().size() > 0)
			m_vbos.push_back(0);
		if (m_geometry->getNormalArray().size() > 0)
			m_vbos.push_back(0);
		if (m_geometry->getTangentArray().size() > 0)
			m_vbos.push_back(0);
		if (m_geometry->getColourArray().size() > 0)
			m_vbos.push_back(0);

		int current_buffer_index = 0;

		glGenBuffers(m_vbos.size(), &m_vbos[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbos[current_buffer_index]);
		glBufferData(GL_ARRAY_BUFFER, m_geometry->getVertexArray().size() * sizeof(m_geometry->getVertexArray()[0]), &m_geometry->getVertexArray()[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		++current_buffer_index;

		if (m_geometry->getTexCoordArray().size() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[current_buffer_index]);
			glBufferData(GL_ARRAY_BUFFER, m_geometry->getTexCoordArray().size() * sizeof(m_geometry->getTexCoordArray()[0]), &m_geometry->getTexCoordArray()[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

			++current_buffer_index;
		}

		if (m_geometry->getNormalArray().size() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[current_buffer_index]);
			glBufferData(GL_ARRAY_BUFFER, m_geometry->getNormalArray().size() * sizeof(m_geometry->getNormalArray()[0]), &m_geometry->getNormalArray()[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

			++current_buffer_index;
		}

		if (m_geometry->getTangentArray().size() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[current_buffer_index]);
			glBufferData(GL_ARRAY_BUFFER, m_geometry->getTangentArray().size() * sizeof(m_geometry->getTangentArray()[0]), &m_geometry->getTangentArray()[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

			++current_buffer_index;
		}

		if (m_geometry->getColourArray().size() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbos[current_buffer_index]);
			glBufferData(GL_ARRAY_BUFFER, m_geometry->getColourArray().size() * sizeof(m_geometry->getColourArray()[0]), &m_geometry->getColourArray()[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, 0);

			++current_buffer_index;
		}

		if (m_geometry->getIndexArray().size() > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbos[current_buffer_index]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_geometry->getIndexArray().size() * sizeof(m_geometry->getIndexArray()[0]), &m_geometry->getIndexArray()[0], GL_STATIC_DRAW);
		}

		return true;
	}

	void MeshAsset::draw() const
	{
		if (m_geometry != NULL)
		{
			glBindVertexArray(m_vao);

			if (m_geometry->getIndexArray().size() > 0)
				glDrawElements(m_geometry->getGeometryType(), m_geometry->getIndexArray().size(), GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(m_geometry->getGeometryType(), 0, m_geometry->getVertexArray().size());
		}
	}

	void MeshAsset::computeBoundingBox()
	{
		m_boundingBox = BoundingBox();

		for (unsigned int i = 0; i < m_geometry->getVertexArray().size(); ++i)
			m_boundingBox.extendBy(m_geometry->getVertexArray()[i]);
	}

	BoundingBox MeshAsset::getBoundingBox() const
	{
		return m_boundingBox;
	}
}