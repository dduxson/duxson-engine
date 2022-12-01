/*!********************************************************************
* File:	Material.h
*
* \brief	Classes that represents the whole material, this can be
*			multiple different textures with different parameters.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include <vector>
#include <map>
#include "ITexture.h"
#include "TextureParameters.h"
#include "IMaterial.h"

namespace DE
{
	class IVisualEngine;

	class Material : public IMaterial
	{
		public:
			Material(TextureParams diffuseTexParams);
			Material(const std::vector<TextureParams>& diffuseTexParams);
			virtual ~Material();

			void bindTextures(std::shared_ptr<IVisualEngine> visualEngine);

			//Ensure not copyable or assignable
			Material(const Material& other) = delete;
			void operator=(const Material& other) = delete;

		private:
			std::map<std::string, ITexture::SPtr> m_uniformNameToTexture;
	};
}