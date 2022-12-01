#pragma once
/*!********************************************************************
* File:	Texture.h
*
* \brief	Classes that holds the textures we require.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#include <map>
#include <memory>
#include <GL/glew.h>
#include "ITexture.h"
#include "TextureParameters.h"

namespace DE
{
	class TextureAsset
	{
		public:
			typedef std::shared_ptr<TextureAsset> SPtr;
			typedef std::weak_ptr<TextureAsset> WPtr;

			/*!
			*	\brief	Constructor for TextureAsset class.
			*/
			TextureAsset(GLenum textureTarget, unsigned int width, unsigned int height, int numTextures, const unsigned char** data, GLfloat* filters,
						 GLenum* internalFormat, GLenum* format, bool clamp, GLenum* attachments);

			/*!
			*	\brief	Destructor for TextureAsset class.
			*/
			virtual ~TextureAsset();

			/*!
			*	\brief	Gets the width of this texture.
			*	\return Width of the texture.
			*/
			int getWidth();

			/*!
			*	\brief	Gets the height of this texture.
			*	\return Height of the texture.
			*/
			int getHeight();

			/*!
			*	\brief	Binds the texture with the given number ready for use.
			*/
			void bind(int texNum) const;

			//Ensure no copy or assignable behaviour
			TextureAsset(TextureAsset& other) = delete;
			void operator=(TextureAsset& other) = delete;

		private:
			/*!
			*	\brief	Setups all the openGL data ready for texture rendering.
			*	\return True if sucessfully generated and set all OpenGL data, false otherwise.
			*/
			bool setupOpenGLTexture(const unsigned char** data, GLfloat* filters,
									GLenum* internalFormat, GLenum* format, bool clamp);

		private:
			GLuint * m_textureID;
			GLenum m_textureTarget;
			//GLuint m_frameBuffer;
			//GLuint m_renderBuffer;
			int m_numTextures;
			int m_width;
			int m_height;
	};

	class Texture : public ITexture
	{
		public:

			/*!
			*	\brief	Constructor for Texture class. Note that if the texture asset
			*			with the name is already present. The rest of the parameters are ignored.
			*/
			Texture(TextureParams params);

			/*!
			*	\brief	Copy constructor for Texture class.
			*/
			Texture(const Texture& texture);

			/*!
			*	\brief	Destructor for Texture class.
			*/
			virtual ~Texture();

			/*!
			*	\brief	Gets the width of this texture.
			*	\return Width of the texture.
			*/
			unsigned int getWidth();

			/*!
			*	\brief	Gets the height of this texture.
			*	\return Height of the texture.
			*/
			unsigned int getHeight();

			/*!
			*	\brief	Binds this texture with the given unit number
			*			ready for use.
			*/
			void bind(unsigned int unit) const;

			//Ensure no assignment
			void operator=(Texture& texture) = delete;

		private:
			TextureAsset::SPtr m_asset;  ///< The asset this texture uses.
			std::string m_fileName;		 ///< Holds the filename (path) or name of the texture.

			static std::map<std::string, TextureAsset::WPtr> ms_assetMap; ///< Map keyed by asset name to the asset object (makes sure no duplicates)
		};
}