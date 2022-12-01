/*!********************************************************************
* File:	Model.h
*
* \brief	Class that holds a full model consisting of multiple meshes
*			and materials.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include <set>
#include <map>
#include "IMesh.h"
#include "IMaterial.h"
#include "Geometry.h"
#include "IModel.h"
#include "TextureParameters.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace DE
{
	class IVisualEngine;

	class Model : public IModel
	{
		public:
			Model(const std::string& filename);
			Model(IMesh::SPtr mesh, IMaterial::SPtr material);
			Model(const std::map<IMesh::WPtr, IMaterial::WPtr, std::owner_less<IMesh::WPtr> >& meshToMaterial);
			virtual ~Model();

			void draw(std::shared_ptr<IVisualEngine> visualEngine) const;
			BoundingBox getBoundingBox() const;

			//Ensure non copyable/assignable
			Model(const Model& other) = delete;
			void operator=(const Model& other) = delete;

		private:
			void createMeshAndMaterial(const aiMesh* aiMesh, const aiScene* scene, const std::string& meshName);
			std::vector<TextureParams> createTextureParams(aiMaterial* aiMaterial, aiTextureType type);
			Geometry::GeometryType getGeometryType(const aiMesh* aiMesh);

			void computeBoundingBox();

		private:
			std::set<IMesh::SPtr> m_meshes;
			std::set<IMaterial::SPtr> m_materials;
			std::map<IMesh::WPtr, IMaterial::WPtr, std::owner_less<IMesh::WPtr> > m_meshToMaterial;
			BoundingBox m_boundingBox;

			std::string m_filename; ///< Filename of the model otherwise empty if not loaded from disk.
	};
}