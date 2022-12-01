#include "./include/TextureParameters.h"

namespace DE
{
	TextureParams::TextureParams(const std::string& _name)
	{
		name = _name;
		textureTarget = GL_TEXTURE_2D;
		filter = GL_LINEAR_MIPMAP_LINEAR;
		internalFormat = GL_RGBA;
		format = GL_RGBA;
		clamp = true;
		attachment = GL_NONE;

		notFile = false;
		width = 0;
		height = 0;
		data = NULL;
	}
}