/*!********************************************************************
* File:	ShaderProgram.h
*
* \brief	Classes that represents a shader program that can be
*			composed of several shaders.
*
* \author	David Duxson
*
* \date	04/10/2015
*
**********************************************************************/
#pragma once
#include <vector>
#include <map>
#include "Shader.h"
#include "IVisualEngine.h"
#include "IShaderProgram.h"

namespace DE
{
	class IVisualEngine;

	class ShaderProgramAsset
	{
		public:
			typedef std::shared_ptr<ShaderProgramAsset> SPtr;
			typedef std::weak_ptr<ShaderProgramAsset> WPtr;

			/*!
			*	\brief	Constructor for ShaderProgramAsset class.
			*	\param[in] fileName	   The path to the shader program file.
			*/
			ShaderProgramAsset(const std::string& fileName);

			/*!
			*	\brief	Destructor for ShaderProgramAsset class.
			*/
			virtual ~ShaderProgramAsset();

			/*!
			*	\brief	Gets whether we are currently holding a sucessfully linked
			*			shader program.
			*	\return True if have sucessfully linked shader program, false otherwise.
			*/
			bool isSuccessfullyLinked();

			/*!
			*	\brief	Binds this shader program so it will be used.
			*/
			void bind();

			/*!
			*	\brief	Gets the map of the uniform locations for this shader program asset.
			*	\return Const reference to a map of shader uniform to it's location.
			*/
			const std::map<ShaderVariable::SPtr, unsigned int>& getUniformLocationMap();

			//Ensure non copyable/assignable
			ShaderProgramAsset(ShaderProgramAsset& other) = delete;
			void operator=(ShaderProgramAsset& other) = delete;

		private:
			/*!
			*	\brief	Creates and links Shader program from the shader program
			*			file.
			*	\param[in] The shader program file to use that defines the shaders.
			*/
			bool linkShaderProgram(const std::string& fileName);

			/*!
			*	\brief	Gets and stores the uniform locations for all shaders.
			*/
			void getUniformLocations();

		private:
			GLuint											m_program;				///< The location of the linked shader program or 0.
			bool											m_isLinked;				///< Whether the program is sucessfully linked.
			std::vector<IShader::SPtr>						m_shaders;				///< The shaders that this program has attached.
			std::map<ShaderVariable::SPtr, unsigned int>	m_uniformToLocation;	///< The uniforms inside the shaders for this program mapped to their location.
	};

	class ShaderProgram : public IShaderProgram
	{
		public:
			/*!
			*	\brief	Constructor for ShaderProgram class.
			*	\param[in] fileName	   The path to the shader program file.
			*/
			ShaderProgram(const std::string& fileName);

			/*!
			*	\brief	Copy Constructor for ShaderProgram class.
			*	\param[in] other The shader to copy.
			*/
			ShaderProgram(const ShaderProgram& other);

			/*!
			*	\brief	Destructor for ShaderProgram class.
			*/
			virtual ~ShaderProgram();

			/*!
			*	\brief	Gets whether we are currently holding a sucessfully linked
			*			shader program.
			*	\return True if have sucessfully linked shader program, false otherwise.
			*/
			bool isSuccessfullyLinked();

			/*!
			*	\brief	Binds this shader program so it will be used.
			*/
			void bind();

			/*!
			*	\brief	Updates all the uniforms in the shader ready for rendering.
			*	\param[in] The visual engine for the current setup. This is used for
			*			   accessing a map of values for uniforms.
			*/
			void updateUniforms(IVisualEngine::SPtr visualEngine);

			//Ensure non assignable
			void operator=(const Shader& other) = delete;


		private:
			void setUniform(unsigned int loc, float value);
			void setUniform(unsigned int loc, int value);
			void setUniform(unsigned int loc, unsigned int value);
			void setUniform(unsigned int loc, const glm::vec2& value);
			void setUniform(unsigned int loc, const glm::vec3& value);
			void setUniform(unsigned int loc, const glm::vec4& value);
			void setUniform(unsigned int loc, const glm::mat2& value);
			void setUniform(unsigned int loc, const glm::mat3& value);
			void setUniform(unsigned int loc, const glm::mat4& value);

		private:
			std::string						m_fileName;		///< The path to the file defining the shaders to use.
			ShaderProgramAsset::SPtr		m_asset;		///< The shader program asset this program uses.

			static std::map<std::string, ShaderProgramAsset::WPtr> ms_asset_map; ///< Map keyed by asset name to the asset object (makes sure no duplicates)
	};
}