#include "./Include/Material.h"
#include "./Include/IVisualEngine.h"
#include "./include/Texture.h"

#include <sstream>

namespace DE
{
	Material::Material(TextureParams diffuseTexParams)
	{
		m_uniformNameToTexture["DEDiffuse1"] = std::make_shared<Texture>(diffuseTexParams);
	}

	Material::Material(const std::vector<TextureParams>& diffuseTexParams)
	{
		for (unsigned int i = 0; i < diffuseTexParams.size(); ++i)
		{
			std::ostringstream ss;
			ss << i;

			m_uniformNameToTexture["DEDiffuse" + ss.str()] = std::make_shared<Texture>(diffuseTexParams[i]);
		}
	}

	Material::~Material()
	{

	}

	void Material::bindTextures(std::shared_ptr<IVisualEngine> visualEngine)
	{
		if (visualEngine != nullptr)
		{
			for (std::map<std::string, Texture::SPtr>::const_iterator it = m_uniformNameToTexture.begin(); it != m_uniformNameToTexture.end(); ++it)
			{
				if (it->second)
					it->second->bind(visualEngine->getSamplerSlot(it->first));
			}
		}
	}
}