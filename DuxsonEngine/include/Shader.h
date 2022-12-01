/*!********************************************************************
* File:	Shader.h
*
* \brief	Class that represents a single shader and it uniforms
* \remark	Uniform reading taken directly from bennybox github.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once

#include <string>
#include <vector>
#include <map>

#include "IShader.h"

namespace DE
{
	class Shader : public IShader
	{
		public:
			typedef std::shared_ptr<Shader> SPtr;
			/*!
			*	\brief	Enum for representing the different types of shaders
			*/
			enum ShaderType
			{
				eVertexShader = GL_VERTEX_SHADER,
				eFragmentShader = GL_FRAGMENT_SHADER
			};

			/*!
			*	\brief	Structure representing structures that are defined within
			*			a shader itself.
			*	\remark Takes ownership of shader variables in structure.
			*/
			struct ShaderStruct
			{
				public:
					typedef std::shared_ptr<ShaderStruct> SPtr;

					ShaderStruct(const std::string& _name, std::vector<ShaderVariable::SPtr> _members)
						: name(_name), members(_members) {}

					std::string name;
					std::vector<ShaderVariable::SPtr> members;
			};

		public:
			/*!
			*	\brief	Constructor for Shader class.
			*	\param[in] eShaderType The type of shader we want.
			*	\param[in] fileName	   The path to the shader source.
			*/
			Shader(ShaderType eShaderType, const std::string& fileName);

			/*!
			*	\brief	Destructor for Shader class.
			*/
			virtual ~Shader();

			/*!
			*	\see IShader
			*/
			bool isSuccessfullyCompiled();

			/*!
			*	\see IShader
			*/
			GLuint getCompiledShader();

			/*!
			*	\see IShader
			*/
			const std::vector<ShaderVariable::SPtr>& getShaderVariables();

		private:
			/*!
			*	\brief	Takes the shader source file and gets to a sucessfully compiled
			*			shader.
			*	\return True if we sucessfully compiled a shader.
			*/
			bool compileShaderFile();

			/*!
			*	\brief	Takes the shader source file and creates shader uniforms
			*			for all uniforms specified in the source.
			*	\param[in] shaderSource The source string for the shader.
			*/
			void detectAllUniforms(const std::string& shaderSource);

			/*!
			*	\brief	Takes the shader source file and creates shader structs
			*			for all structures specified in the source.
			*	\param[in] shaderSource The source string for the shader.
			*/
			void detectAllStructs(const std::string& shaderSource);

			/*!
			*	\brief	Finds the shader structs name from the string supplied.
			*	\param[in] startToOpeningBrace String of just after struct keyword and space
			*								   to just before the opening brace.
			*/
			std::string findShaderStructName(const std::string& startToOpeningBrace);

			/*!
			*	\brief	Finds the shader structs members from the string supplied.
			*	\param[in] openingBraceToClosingBrace String of opening brace
			*										  to just before the closing brace.
			*/
			std::vector<ShaderVariable::SPtr> findUniformStructMembers(const std::string& openingBraceToClosingBrace);

		private:
			GLenum			m_eShaderType;			///< The type of the shader we hold.
			std::string		m_fileName;				///< The path to the shader source.

			bool			m_isCompiled;			///< Whether the shader we have is fully compiled.
			GLuint			m_shader;				///< The location of the shader or 0.

			std::vector<ShaderVariable::SPtr>			m_uniforms;		///< The uniforms this shader contains.
			std::map<std::string, ShaderStruct::SPtr>	m_nameToStruct;	///< Map of the structures this shader contains keyed by name.
	};
}