/*!********************************************************************
* File:	IShader.h
*
* \brief	Interface that represents a single shader and it uniforms
* \remark	Uniform reading taken directly from bennybox github.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once
#include <GL/glew.h>
#include "ShaderVariable.h"

namespace DE
{
	class IShader
	{
		public:
			typedef std::shared_ptr<IShader> SPtr;

			IShader() {}
			virtual ~IShader() {}

			/*!
			*	\brief	Gets whether we are currently holding a sucessfully compiled
			*			shader.
			*	\return True if have sucessfully compiled shader, false otherwise.
			*/
			virtual bool isSuccessfullyCompiled() = 0;

			/*!
			*	\brief	Gets the location of the shader.
			*	\return Location of shader, 0 if no location.
			*/
			virtual GLuint getCompiledShader() = 0;

			/*!
			*	\brief	Gets the uniforms contained in this shader.
			*	\return A const reference to the shader uniforms array.
			*/
			virtual const std::vector<ShaderVariable::SPtr>& getShaderVariables() = 0;
	};
}