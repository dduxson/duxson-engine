#include "./Include/Texture.h"
#include "./Include/Logger.h"
#include <SFML/Graphics/Image.hpp>

#include <iostream>

namespace DE
{
	std::map<std::string, TextureAsset::WPtr> Texture::ms_assetMap;

	TextureAsset::TextureAsset(GLenum textureTarget, unsigned int width, unsigned int height, int numTextures, const unsigned char** data, GLfloat* filters,
		GLenum* internalFormat, GLenum* format, bool clamp, GLenum* attachments)
		: m_textureTarget(textureTarget)
		, m_numTextures(numTextures)
		, m_width(width)
		, m_height(height)
	{
		m_textureID = new GLuint[numTextures];

		setupOpenGLTexture(data, filters, internalFormat, format, clamp);
		//setupOpenGLRenderTargets(attachments);
	}

	TextureAsset::~TextureAsset()
	{
		if (*m_textureID)
			glDeleteTextures(m_numTextures, m_textureID);
		if (m_textureID)
			delete[] m_textureID;

		Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Deleted texture asset with name.");
	}

	int TextureAsset::getWidth()
	{
		return m_width;
	}

	int TextureAsset::getHeight()
	{
		return m_height;
	}

	void TextureAsset::bind(int texNum) const
	{
		glBindTexture(m_textureTarget, m_textureID[texNum]);
	}

	bool TextureAsset::setupOpenGLTexture(const unsigned char** data, GLfloat* filters,
		GLenum* internalFormat, GLenum* format, bool clamp)
	{
		static const float MAX_ANISTROPIC_ALLOWED = 8.0f;

		glGenTextures(m_numTextures, m_textureID);

		for (int i = 0; i < m_numTextures; ++i)
		{
			glBindTexture(m_textureTarget, m_textureID[i]);

			glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, filters[i]);
			glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, filters[i]);

			if (clamp)
			{
				glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glTexImage2D(m_textureTarget, 0, internalFormat[i], m_width, m_height, 0, format[i], GL_UNSIGNED_BYTE, data[i]);

			//If we require mip mapping, generate the mip map and apply anistropic filtering.
			if (filters[i] == GL_NEAREST_MIPMAP_NEAREST || filters[i] == GL_NEAREST_MIPMAP_LINEAR ||
				filters[i] == GL_LINEAR_MIPMAP_NEAREST || filters[i] == GL_LINEAR_MIPMAP_LINEAR)
			{
				glGenerateMipmap(m_textureTarget);

				GLfloat maxAnisotropy;
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);

				//Clamp within sensible values
				if (maxAnisotropy < 0.0f)
					maxAnisotropy = 0.0f;
				if (maxAnisotropy > MAX_ANISTROPIC_ALLOWED)
					maxAnisotropy = MAX_ANISTROPIC_ALLOWED;

				glTexParameterf(m_textureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);
			}
			else
			{
				glTexParameteri(m_textureTarget, GL_TEXTURE_BASE_LEVEL, 0);
				glTexParameteri(m_textureTarget, GL_TEXTURE_MAX_LEVEL, 0);
			}
		}

		return true;
	}

	Texture::Texture(TextureParams params)
		: m_fileName(params.name)
	{
		std::map<std::string, TextureAsset::WPtr>::const_iterator it = ms_assetMap.find(m_fileName);

		if (params.notFile)
		{
			if (it != ms_assetMap.end() && (!it->second.expired()))
			{
				Logger::Instance()->writeToLogFile(Logger::eLogError, "Failed to create texture asset with name: %s as one with this name already exists.", m_fileName.c_str());
			}
			else
			{
				const unsigned char* data = const_cast<const unsigned char*>(params.data);

				m_asset = std::make_shared<TextureAsset>(params.textureTarget, params.width, params.height, 1, &data, &params.filter,
					&params.internalFormat, &params.format, params.clamp, &params.attachment);
				ms_assetMap[m_fileName] = m_asset;

				Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Created texture asset with name: %s.", m_fileName.c_str());
			}
		}
		else
		{
			if (it != ms_assetMap.end() && (!it->second.expired()))
			{
				m_asset = it->second.lock();
			}
			else
			{
				sf::Image image;

				if (!image.loadFromFile(m_fileName))
					Logger::Instance()->writeToLogFile(Logger::eLogError, "Failed to load image with name: %s", m_fileName.c_str());
				else
					Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Sucessfully loaded image with name: %s", m_fileName.c_str());

				sf::Vector2u imageSize = image.getSize();
				const unsigned char* data = image.getPixelsPtr();

				m_asset = std::make_shared<TextureAsset>(params.textureTarget, imageSize.x, imageSize.y, 1, &data, &params.filter,
					&params.internalFormat, &params.format, params.clamp, &params.attachment);
				ms_assetMap[m_fileName] = m_asset;

				Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Created texture asset with name: %s", m_fileName.c_str());
			}
		}
	}

	Texture::Texture(const Texture& texture)
		: m_asset(texture.m_asset),
		m_fileName(texture.m_fileName)
	{
		
	}

	Texture::~Texture()
	{
		
	}

	unsigned int Texture::getWidth()
	{
		if (m_asset != nullptr)
			return m_asset->getWidth();

		return 0;
	}

	unsigned int Texture::getHeight()
	{
		if (m_asset != nullptr)
			return m_asset->getHeight();

		return 0;
	}

	void Texture::bind(unsigned int unit) const
	{
		//Only 32 texture units allowed in OpenGL.
		if (unit >= 0 && unit < 32)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			m_asset->bind(0);
		}
	}
}