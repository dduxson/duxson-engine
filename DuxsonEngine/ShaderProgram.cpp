#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include "./Include/ShaderProgram.h"
#include "./Include/Shader.h"
#include "./Include/Logger.h"
#include "./Include/IVisualEngine.h"

namespace DE
{
	std::map<std::string, ShaderProgramAsset::WPtr> ShaderProgram::ms_asset_map;

	ShaderProgram::ShaderProgram(const std::string& fileName)
		: m_fileName(fileName)
	{
		std::map<std::string, ShaderProgramAsset::WPtr>::const_iterator it = ms_asset_map.find(m_fileName);

		if (it != ms_asset_map.end() && (!it->second.expired()))
		{
			m_asset = it->second.lock();
		}
		else
		{
			m_asset = std::make_shared<ShaderProgramAsset>(m_fileName);
			ms_asset_map[fileName] = m_asset;

			Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Created shader program asset with name: %s.", m_fileName.c_str());
		}
	}

	ShaderProgram::ShaderProgram(const ShaderProgram& other)
		: m_asset(other.m_asset)
		, m_fileName(other.m_fileName)
	{

	}

	ShaderProgram::~ShaderProgram()
	{

	}

	bool ShaderProgram::isSuccessfullyLinked()
	{
		if (!m_asset)
			return false;

		return m_asset->isSuccessfullyLinked();
	}

	void ShaderProgram::bind()
	{
		if (m_asset)
			m_asset->bind();
	}

	void ShaderProgram::updateUniforms(IVisualEngine::SPtr visualEngine)
	{
		if (visualEngine != nullptr && m_asset != nullptr)
		{
			//First add a built in uniform for the complete transformation matrix.
			glm::mat4 viewProjMatrix = visualEngine->getShaderUniformMap().getMat4("DEViewProjectionMatrix");
			glm::mat4 modelMatrix = visualEngine->getShaderUniformMap().getMat4("DEModelMatrix");

			visualEngine->getShaderUniformMap().set("DEModelViewProjectionMatrix", viewProjMatrix * modelMatrix);

			//Now process all uniforms this shader program has.
			ShaderVariableMap& uniformValueMap = visualEngine->getShaderUniformMap();
			const std::map<ShaderVariable::SPtr, unsigned int>& shaderUniformLocs = m_asset->getUniformLocationMap();

			for (std::map<ShaderVariable::SPtr, unsigned int>::const_iterator it = shaderUniformLocs.begin(); it != shaderUniformLocs.end(); ++it)
			{
				switch (it->first->getType())
				{
				case ShaderVariable::eFloat:
					setUniform(it->second, uniformValueMap.getFloat(it->first->getName()));
					break;
				case ShaderVariable::eInt:
					setUniform(it->second, uniformValueMap.getInt(it->first->getName()));
					break;
				case ShaderVariable::eUnsignedInt:
					setUniform(it->second, uniformValueMap.getUInt(it->first->getName()));
					break;
				case ShaderVariable::eVec2:
					setUniform(it->second, uniformValueMap.getVec2(it->first->getName()));
					break;
				case ShaderVariable::eVec3:
					setUniform(it->second, uniformValueMap.getVec3(it->first->getName()));
					break;
				case ShaderVariable::eVec4:
					setUniform(it->second, uniformValueMap.getVec4(it->first->getName()));
					break;
				case ShaderVariable::eMat2:
					setUniform(it->second, uniformValueMap.getMat2(it->first->getName()));
					break;
				case ShaderVariable::eMat3:
					setUniform(it->second, uniformValueMap.getMat3(it->first->getName()));
					break;
				case ShaderVariable::eMat4:
					setUniform(it->second, uniformValueMap.getMat4(it->first->getName()));
					break;
				case ShaderVariable::eSampler:
					setUniform(it->second, int(visualEngine->getSamplerSlot(it->first->getName())));
					break;
				}
			}
		}
	}

	void ShaderProgram::setUniform(unsigned int loc, float value)
	{
		glUniform1f(loc, value);
	}

	void ShaderProgram::setUniform(unsigned int loc, int value)
	{
		glUniform1i(loc, value);
	}

	void ShaderProgram::setUniform(unsigned int loc, unsigned int value)
	{
		glUniform1ui(loc, value);
	}

	void ShaderProgram::setUniform(unsigned int loc, const glm::vec2& value)
	{
		glUniform2f(loc, value.x, value.y);
	}

	void ShaderProgram::setUniform(unsigned int loc, const glm::vec3& value)
	{
		glUniform3f(loc, value.x, value.y, value.z);
	}

	void ShaderProgram::setUniform(unsigned int loc, const glm::vec4& value)
	{
		glUniform4f(loc, value.x, value.y, value.z, value.w);
	}

	void ShaderProgram::setUniform(unsigned int loc, const glm::mat2& value)
	{
		glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderProgram::setUniform(unsigned int loc, const glm::mat3& value)
	{
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderProgram::setUniform(unsigned int loc, const glm::mat4& value)
	{
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
	}

	ShaderProgramAsset::ShaderProgramAsset(const std::string& fileName)
		: m_program(0)
		, m_isLinked(false)
	{
		m_isLinked = linkShaderProgram(fileName);
	}

	ShaderProgramAsset::~ShaderProgramAsset()
	{
		for (unsigned int i = 0; i < m_shaders.size(); ++i)
			glDetachShader(m_program, m_shaders[i]->getCompiledShader());

		m_shaders.clear();
		m_uniformToLocation.clear();

		glDeleteProgram(m_program);

		Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Deleted shader program asset.");
	}

	bool ShaderProgramAsset::isSuccessfullyLinked()
	{
		return m_isLinked;
	}

	void ShaderProgramAsset::bind()
	{
		glUseProgram(m_program);
	}

	const std::map<ShaderVariable::SPtr, unsigned int>& ShaderProgramAsset::getUniformLocationMap()
	{
		return m_uniformToLocation;
	}

	bool ShaderProgramAsset::linkShaderProgram(const std::string& fileName)
	{
		m_program = glCreateProgram();

		if (m_program == 0)
		{
			Logger::Instance()->writeToLogFile(Logger::eLogError, "Failed to create a GL shader program for %s.", fileName.c_str());
			return false;
		}

		//Use the given file to get the paths to the shaders to use.
		std::ifstream programFile(fileName.c_str());

		if (!programFile.is_open())
		{
			Logger::Instance()->writeToLogFile(Logger::eLogError, "Failed to find shader program file %s.", fileName.c_str());
			return false;
		}

		std::string shaderPath;
		bool failed = false;

		while (getline(programFile, shaderPath))
		{
			//Determine type of shader using file extension (should suffice for now)
			IShader::SPtr shader;

			if (shaderPath.find(".vert") != std::string::npos)
				shader = std::make_shared<Shader>(Shader::eVertexShader, shaderPath);
			else if (shaderPath.find(".frag") != std::string::npos)
				shader = std::make_shared<Shader>(Shader::eFragmentShader, shaderPath);

			if (shader != nullptr)
			{
				if (shader->isSuccessfullyCompiled())
				{
					m_shaders.push_back(shader);
					glAttachShader(m_program, shader->getCompiledShader());
				}
				else
				{
					failed = true;
					break;
				}
			}
		}

		programFile.close();

		if (failed)
			return false;

		glLinkProgram(m_program);

		GLint status;
		glGetProgramiv(m_program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLchar strInfoLog[1024];
			glGetProgramInfoLog(m_program, 1024, NULL, strInfoLog);
			Logger::Instance()->writeToLogFile(Logger::eLogError, "ShaderProgram - Linker failure: %s", strInfoLog);

			return false;
		}

		getUniformLocations();

		Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Sucessfully linked shader program %s with %d shaders.", fileName.c_str(), m_shaders.size());

		return true;
	}

	void ShaderProgramAsset::getUniformLocations()
	{
		for (unsigned int iShader = 0; iShader < m_shaders.size(); ++iShader)
		{
			const std::vector<ShaderVariable::SPtr>& uniforms = m_shaders[iShader]->getShaderVariables();

			for (unsigned int iUniform = 0; iUniform < uniforms.size(); ++iUniform)
			{
				int location = glGetUniformLocation(m_program, uniforms[iUniform]->getName().c_str());

				if (location > -1)
					m_uniformToLocation[uniforms[iUniform]] = location;
				else
					Logger::Instance()->writeToLogFile(Logger::eLogWarning, "ShaderProgram - failed to find uniform location: %s", uniforms[iUniform]->getName().c_str());
			}
		}
	}
}