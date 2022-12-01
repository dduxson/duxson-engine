/*!********************************************************************
* File:	TextureParameters.h
*
* \brief	Class that holds the parameters for a texture creation.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once
#include <string>
#include <GL/glew.h>

namespace DE
{
	struct TextureParams
	{
		public:
			std::string name;
			GLenum textureTarget;
			GLfloat filter;
			GLenum internalFormat;
			GLenum format;
			bool clamp;
			GLenum attachment;

			//Parameters below here only required if we are not
			//loading from a file on disk but creating one.
			bool notFile;
			unsigned int width;
			unsigned int height;
			unsigned char* data;

		public:
			TextureParams(const std::string& _name);
	};
}