/*!********************************************************************
* File:	Mesh.h
*
* \brief	Classes that hold the geometry of objects and the OpenGL
*			specifics required to render the geometry.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include <map>
#include <GL/glew.h>
#include "Geometry.h"
#include "IMesh.h"
#include <string>

namespace DE
{
	class MeshAsset
	{
		public:
			typedef std::shared_ptr<MeshAsset> SPtr;
			typedef std::weak_ptr<MeshAsset> WPtr;

			/*!
			*	\brief	Constructor for MeshAsset class.
			*	\param[in] geometry	shared pointer for geometry
			*/
			MeshAsset(Geometry::SPtr geometry);

			/*!
			*	\brief	Destructor for MeshAsset class.
			*/
			virtual ~MeshAsset();

			/*!
			*	\brief	Does some basic size checking to see if the geometry looks
			*			valid.
			*	\return True if looks valid, false otherwise.
			*/
			bool isValid();

			/*!
			*	\brief	Draws the geometry to screen.
			*/
			void draw() const;

			/*!
			*	\brief	Gets the bounding box for this mesh asset.
			*	\return Bounding box for this mesh asset.
			*/
			BoundingBox getBoundingBox() const;

			//Ensure non copyable and assignable.
			MeshAsset(MeshAsset& other) = delete;
			void operator=(MeshAsset& other) = delete;

		private:
			/*!
			*	\brief	Clears out vbos and deletes geometry we own.
			*/
			void clearGeometry();

			/*!
			*	\brief	Setups all the openGL vao, vbos etc ready for rendering.
			*	\return True if sucessfully generated all OpenGL data, false otherwise.
			*/
			bool setupOpenGLData();

			/*!
			*	\brief	Computes the bounding box for this mesh.
			*/
			void computeBoundingBox();

		private:
			Geometry::SPtr		m_geometry;		///< Holds and owns the geometry of for this mesh.	
			GLuint				m_vao;			///< The location of the vertex array object.
			std::vector<GLuint> m_vbos;			///< The location of the vertex buffer objects.
			BoundingBox			m_boundingBox;	///< The bounding box of this mesh
	};

	class Mesh : public IMesh
	{
		public:
			/*!
			*	\brief	Constructor for Mesh class.
			*	\param[in] name	  The name of the mesh
			*	\param[in] geom	  The geometry that this mesh should use
			*/
			Mesh(const std::string& name, Geometry::SPtr geom);

			/*!
			*	\brief	Copy constructor for Mesh.
			*/
			Mesh(const Mesh& mesh);

			/*!
			*	\brief	Destructor for Mesh class.
			*/
			virtual ~Mesh();

			/*!
			*	\brief	Does some basic size checking to see if the geometry looks
			*			valid.
			*	\return True if looks valid, false otherwise.
			*/
			bool isValid();

			/*!
			*	\brief	Draws the geometry to screen.
			*/
			void draw() const;

			/*!
			*	\brief	Gets the bounding box for this mesh asset.
			*	\return Bounding box for this mesh asset.
			*/
			BoundingBox getBoundingBox() const;

			//Ensure non assignable.
			void operator=(Mesh& mesh) = delete;

		private:
			std::string						m_name;				///< Holds the filename (path) or name of the mesh.
			std::shared_ptr<MeshAsset>		m_asset;			///< The asset this mesh uses

			static std::map<std::string, std::weak_ptr<MeshAsset> > ms_asset_map; ///< Map keyed by asset name to the asset object (makes sure no duplicates)
	};
}