/*!********************************************************************
* File:	TerrainHeightMapComponent.h
*
* \brief	Class that handles creating a terrain based upon the given
*			heightmap.
*
* \author	David Duxson
*
* \date	20/12/2015
*
**********************************************************************/
#pragma once

#include <vector>
#include "ModelVisualEntityComponent.h"

namespace sf
{
	class Image;
}

namespace DE
{
	class TerrainHeightMapComponent : public ModelVisualEntityComponent
	{
		public:
			typedef std::shared_ptr<TerrainHeightMapComponent> SPtr;
			typedef std::weak_ptr<TerrainHeightMapComponent> WPtr;

			TerrainHeightMapComponent(const std::string& heightMapFilename, const std::string& textureFilename, IShaderProgram::SPtr prog,
									  unsigned int texXRepeatPxls = 10, unsigned int texYRepeatPxls = 10);

			virtual ~TerrainHeightMapComponent();

			virtual void render(IVisualEngine::SPtr visualEngine) const;

			double getWorldHeight(double x, double z);

		protected:
			void generateVerticesAndTexCoords(const sf::Image & image, std::vector<std::vector<glm::vec3>>& vertices, std::vector<std::vector<glm::vec2>>& texCoords,
											  unsigned int texXRepeatPxls, unsigned int texYRepeatPxls);
			double barryCentricInterpolation(const glm::vec3 & p1, const glm::vec3 & p2, const glm::vec3 & p3, const glm::vec2 & pos);

		private:
			std::vector< std::vector<glm::vec3> > m_vertices;
	};
}
