#include "./Include/Model.h"
#include "./Include/VisualEngine.h"
#include "./include/Mesh.h"
#include "./include/Material.h"
#include "./include/Geometry.h"
#include "./Include/Logger.h"

#include <sstream>
#include <string>

namespace DE
{
	Model::Model(const std::string& filename)
		: m_filename(filename)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(filename.c_str(),
			aiProcess_CalcTangentSpace |
			aiProcess_GenSmoothNormals |
			aiProcess_Triangulate |
			aiProcess_FlipUVs);

		if (!scene)
		{
			Logger::Instance()->writeToLogFile(Logger::eLogError, "Assimp failed to load scene from file: %s", filename.c_str());
			return;
		}

		//Create all meshes for this model
		for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
		{
			std::ostringstream ss;
			ss << i;

			createMeshAndMaterial(scene->mMeshes[i], scene, std::string(filename + "_") + ss.str());
		}

		computeBoundingBox();
	}

	Model::Model(IMesh::SPtr mesh, IMaterial::SPtr material)
	{
		if (mesh != nullptr)
		{
			m_meshes.insert(mesh);

			if (material != nullptr)
				m_materials.insert(material);

			m_meshToMaterial[mesh] = material;
		}
		else
		{
			Logger::Instance()->writeToLogFile(Logger::eLogWarning, "Created model with no meshes or materials");
		}

		computeBoundingBox();
	}

	Model::Model(const std::map<IMesh::WPtr, IMaterial::WPtr, std::owner_less<IMesh::WPtr> >& meshToMaterial)
		: m_meshToMaterial(meshToMaterial)
	{
		for (std::map<IMesh::WPtr, IMaterial::WPtr>::const_iterator it = meshToMaterial.begin(); it != meshToMaterial.end(); ++it)
		{
			if (!it->first.expired() && (!it->second.expired()))
			{
				m_meshes.insert(it->first.lock());
				m_materials.insert(it->second.lock());
			}
		}

		if (m_meshes.size() == 0)
			Logger::Instance()->writeToLogFile(Logger::eLogWarning, "Created model with no meshes or materials");

		computeBoundingBox();
	}

	Model::~Model()
	{
		bool test = true;
	}

	void Model::createMeshAndMaterial(const aiMesh* aiMesh, const aiScene* scene, const std::string& meshName)
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> tangents;
		std::vector<unsigned int> indices;

		const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);

		Geometry::GeometryType geoType = getGeometryType(aiMesh);

		if (geoType == Geometry::eInvalidGeometry)
		{
			Logger::Instance()->writeToLogFile(Logger::eLogWarning, "Assimp import has multiple primitive type geometry in a mesh - unsupported.");
			return;
		}

		for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
		{
			const aiVector3D pos = aiMesh->mVertices[i];
			const aiVector3D normal = aiMesh->mNormals[i];
			const aiVector3D texCoord = aiMesh->HasTextureCoords(0) ? aiMesh->mTextureCoords[0][i] : aiZeroVector; //Can have up to 8 tex coords so we just take first!
			const aiVector3D tangent = aiMesh->mTangents[i];

			vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
			normals.push_back(glm::vec3(normal.x, normal.y, normal.z));
			texCoords.push_back(glm::vec2(texCoord.x, texCoord.y));
			tangents.push_back(glm::vec3(tangent.x, tangent.y, tangent.z));
		}

		for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
		{
			const aiFace& face = aiMesh->mFaces[i];

			if (geoType == Geometry::eTriangleGeometry && face.mNumIndices == 3)
			{
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);
			}
			else if (geoType == Geometry::ePointGeometry && face.mNumIndices == 1)
			{
				indices.push_back(face.mIndices[0]);
			}
			else if (geoType == Geometry::eLineGeometry && face.mNumIndices == 2)
			{
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
			}
			else
			{
				Logger::Instance()->writeToLogFile(Logger::eLogError, "Assimp face had wrong number of indicies");
			}
		}

		DE::Geometry::SPtr geom = std::make_shared<Geometry>(indices, vertices, texCoords, normals, tangents);
		geom->setGeometryType(geoType);

		if (geom->isValid())
		{
			IMesh::SPtr mesh = std::make_shared<Mesh>(meshName, geom);
			IMaterial::SPtr material;

			//Take care of material if this mesh has one.
			if (aiMesh->mMaterialIndex >= 0)
			{
				aiMaterial* aiMaterial = scene->mMaterials[aiMesh->mMaterialIndex];

				std::vector<TextureParams> diffuse_texs = createTextureParams(aiMaterial, aiTextureType_DIFFUSE);

				if (diffuse_texs.size() > 0)
					material = std::make_shared<Material>(diffuse_texs);
			}

			m_meshes.insert(mesh);
			m_materials.insert(material);
			m_meshToMaterial[mesh] = material;
		}
		else
		{
			Logger::Instance()->writeToLogFile(Logger::eLogError, "Geometry created from Assimp was invalid from file: ", m_filename.c_str());
		}
	}

	Geometry::GeometryType Model::getGeometryType(const aiMesh* aiMesh)
	{
		bool containsPoints = (aiMesh->mPrimitiveTypes & aiPrimitiveType_POINT) == aiPrimitiveType_POINT;
		bool containsLines = (aiMesh->mPrimitiveTypes & aiPrimitiveType_LINE) == aiPrimitiveType_LINE;
		bool containsTris = (aiMesh->mPrimitiveTypes & aiPrimitiveType_TRIANGLE) == aiPrimitiveType_TRIANGLE;

		if (containsPoints && (!containsLines) && (!containsTris))
			return Geometry::ePointGeometry;
		else if ((!containsPoints) && containsLines && (!containsTris))
			return Geometry::eLineGeometry;
		else if ((!containsPoints) && (!containsLines) && containsTris)
			return Geometry::eTriangleGeometry;
		else
			return Geometry::eInvalidGeometry;
	}

	std::vector<TextureParams> Model::createTextureParams(aiMaterial* aiMaterial, aiTextureType type)
	{
		std::vector<TextureParams> returnTexParams;

		for (GLuint i = 0; i < aiMaterial->GetTextureCount(type); ++i)
		{
			aiString str;
			aiMaterial->GetTexture(type, i, &str);

			TextureParams texParams(str.C_Str());
			returnTexParams.push_back(texParams);
		}

		return returnTexParams;
	}

	void Model::draw(std::shared_ptr<IVisualEngine> visualEngine) const
	{
		for (std::map<IMesh::WPtr, IMaterial::WPtr>::const_iterator it = m_meshToMaterial.begin(); it != m_meshToMaterial.end(); ++it)
		{
			if (!it->second.expired())
				it->second.lock()->bindTextures(visualEngine);

			if (!it->first.expired())
				it->first.lock()->draw();
		}
	}

	void Model::computeBoundingBox()
	{
		m_boundingBox = BoundingBox();

		for (std::set<IMesh::SPtr>::const_iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
			m_boundingBox.extendBy((*it)->getBoundingBox());
	}

	BoundingBox Model::getBoundingBox() const
	{
		return m_boundingBox;
	}
}