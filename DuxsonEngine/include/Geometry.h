/*!********************************************************************
 * File:	Geometry.h										
 *
 * \brief	Class that stores the geometry of an object (not OpenGL
 *			specific).
 *
 * \author	David Duxson
 *
 * \date	04/03/2015
 *
 **********************************************************************/
#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <memory>

namespace DE
{
	class Geometry
	{
		public:
			typedef std::shared_ptr<Geometry> SPtr;

			/*!
			 *	\brief	Enum that defines the type of geometry we have. Currently
			 *			supports points, lines and triangles.
			 */
			enum GeometryType
			{
				eInvalidGeometry = -1,
				ePointGeometry = GL_POINTS,
				eLineGeometry = GL_LINES,
				eLineStripGeometry = GL_LINE_STRIP,
				eLineLoopGeometry = GL_LINE_LOOP,
				eTriangleGeometry = GL_TRIANGLES,
				eTriangleStripGeometry = GL_TRIANGLE_STRIP,
				eTriangleFanGeometry = GL_TRIANGLE_FAN
			};

		public:
			/*!
			 *	\brief	Constructor for Geometry class.
			 *	\param[in] indicies The order of in which to draw the indicies.
			 *	\param[in] vertices The vertices of the geometry
			 *	\param[in] texCoords The texture cooridnates for the geometry (optional)
			 *	\param[in] normals The normals for the geometry (optional - can compute these too)
			 *	\param[in] tangents The tangents for the geometry (optional - can compute these too)
			 */
			Geometry(const std::vector<unsigned int>& indicies, const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& texCoords = std::vector<glm::vec2>(),
					const std::vector<glm::vec3>& normals = std::vector<glm::vec3>(), const std::vector<glm::vec3>& tangents = std::vector<glm::vec3>(), 
					const std::vector<glm::vec4>& colours = std::vector<glm::vec4>());
			
			/*!
			 *	\brief	Copy constructor for Geometry class.
			 *	\param[in] geometry The geometry to copy.
			 */
			Geometry(const Geometry& geometry);

			/*!
			 *	\brief	Does some basic size checking to see if the geometry looks
			 *			valid.
			 *	\return True if looks valid, false otherwise.
			 */
			virtual bool isValid() const;

			/*!
			 *	\brief	Generates Normals and Tangents if they do not already exist.
			 *	\return True if looks finalize ran ok, false otherwise
			 */
			virtual bool finalizeGeom();

			/*!
			 *	\brief	Gets the indicies of the geometry
			 *	\return Const reference to indicies of the geometry.
			 */
			const std::vector<unsigned int>&	getIndexArray() const;
			
			/*!
			 *	\brief	Gets the vertices of the geometry
			 *	\return Const reference to vertices of the geometry.
			 */
			const std::vector<glm::vec3>&		getVertexArray() const;

			/*!
			 *	\brief	Gets the texture coordiantes of the geometry
			 *	\return Const reference to texture coordiantes of the geometry.
			 */
			const std::vector<glm::vec2>&		getTexCoordArray() const;

			/*!
			 *	\brief	Gets the normals of the geometry
			 *	\return Const reference to normals of the geometry.
			 */
			const std::vector<glm::vec3>&		getNormalArray() const;

			/*!
			 *	\brief	Gets the tangents of the geometry
			 *	\return Const reference to tangents of the geometry.
			 */
			const std::vector<glm::vec3>&		getTangentArray() const;

			/*!
			 *	\brief	Gets the colours of the geometry
			 *	\return Const reference to colours of the geometry.
			 */
			const std::vector<glm::vec4>&		getColourArray() const;

			/*!
			 *	\brief	Gets the type of the geometry
			 *	\return The type of geometry as an enum.
			 */	
			GeometryType getGeometryType() const;

			/*!
			 *	\brief	Sets the type of the geometry
			 *	\param[in] type The type of geometry as an enum.
			 */	
			void setGeometryType(GeometryType type);

		protected:
			/*!
			*	\brief	Protected constructor so that child classes can start with an empty
			*			geometry.
			*/
			Geometry();

			/*!
			 *	\brief	Calculate the normals for the geometry.
			 */
			virtual void calcNormals();
			
			/*!
			 *	\brief	Calculate the tangents for the geometry.
			 */
			virtual void calcTangents();

		protected:
			std::vector<unsigned int>	m_indicies;		///< The indicies for the geometry
			std::vector<glm::vec3>		m_vertices;		///< The vertices for the geometry
			std::vector<glm::vec2>		m_texCoords;	///< The texture coordinates for the geometry
			std::vector<glm::vec3>		m_normals;		///< The normals for the geometry
			std::vector<glm::vec3>		m_tangents;		///< The tangents for the geometry
			std::vector<glm::vec4>		m_colours;		///< The colours for the geometry

			GeometryType				m_type;			///< The type of the geometry
	};
}