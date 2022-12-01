#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include "./Include/Shader.h"
#include "./Include/Logger.h"

namespace DE
{
	Shader::Shader(ShaderType eShaderType, const std::string& fileName)
		: m_eShaderType(eShaderType)
		, m_fileName(fileName)
		, m_isCompiled(false)
		, m_shader(0)
	{
		m_isCompiled = compileShaderFile();
	}

	Shader::~Shader()
	{
		glDeleteShader(m_shader);
		m_uniforms.clear();
		m_nameToStruct.clear();
	}

	bool Shader::isSuccessfullyCompiled()
	{
		return m_isCompiled;
	}

	GLuint Shader::getCompiledShader()
	{
		return m_shader;
	}

	const std::vector<ShaderVariable::SPtr>& Shader::getShaderVariables()
	{
		return m_uniforms;
	}

	bool Shader::compileShaderFile()
	{
		std::ifstream shaderFile(m_fileName.c_str());

		if (!shaderFile.is_open())
		{
			Logger::Instance()->writeToLogFile(Logger::eLogError, "Failed to find shader file %s.", m_fileName.c_str());
			return false;
		}

		std::stringstream shaderData;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();

		std::string strShaderData = shaderData.str();

		detectAllStructs(strShaderData);
		detectAllUniforms(strShaderData);

		const GLchar* p[1];
		p[0] = strShaderData.c_str();
		GLint lengths[1];
		lengths[0] = strShaderData.length();

		m_shader = glCreateShader(m_eShaderType);
		glShaderSource(m_shader, 1, p, lengths);
		glCompileShader(m_shader);

		GLint status;
		glGetShaderiv(m_shader, GL_COMPILE_STATUS, &status);

		if (status == GL_FALSE)
		{
			GLchar strInfoLog[1024];
			glGetShaderInfoLog(m_shader, 1024, NULL, strInfoLog);

			const char *strShaderType = NULL;

			switch (m_eShaderType)
			{
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			}

			Logger::Instance()->writeToLogFile(Logger::eLogError, "Compile failure in %s shader: %s.", strShaderType, strInfoLog);

			return false;
		}

		Logger::Instance()->writeToLogFile(Logger::eLogMessage, "Sucessfully compiled shader file %s.", m_fileName.c_str());

		return true;
	}

	void Shader::detectAllUniforms(const std::string& shaderSource)
	{
		static const std::string UNIFORM_KEY = "uniform";

		size_t uniformLocation = shaderSource.find(UNIFORM_KEY);

		while (uniformLocation != std::string::npos)
		{
			bool isCommented = false;
			size_t lastLineEnd = shaderSource.rfind("\n", uniformLocation);

			//Check not commented out
			if (lastLineEnd != std::string::npos)
			{
				std::string potentialCommentSection = shaderSource.substr(lastLineEnd, uniformLocation - lastLineEnd);
				isCommented = potentialCommentSection.find("//") != std::string::npos;
			}

			if (!isCommented)
			{
				size_t begin = uniformLocation + UNIFORM_KEY.length();
				size_t end = shaderSource.find(";", begin);

				std::string uniformLine = shaderSource.substr(begin + 1, end - begin - 1);

				begin = uniformLine.find(" ");
				std::string uniformName = uniformLine.substr(begin + 1);
				std::string shaderVariableType = uniformLine.substr(0, begin);

				if (m_nameToStruct.find(shaderVariableType) != m_nameToStruct.end())
				{
					ShaderStruct::SPtr baseStruct = m_nameToStruct[shaderVariableType];

					//Add this structs members.
					for (unsigned int i = 0; i < baseStruct->members.size(); ++i)
						m_uniforms.push_back(std::make_shared<ShaderVariable>(uniformName + "." + baseStruct->members[i]->getName(), baseStruct->members[i]->getType()));
				}
				else
					m_uniforms.push_back(std::make_shared<ShaderVariable>(uniformName, ShaderVariable::GetShaderVariableType(shaderVariableType)));
			}

			uniformLocation = shaderSource.find(UNIFORM_KEY, uniformLocation + UNIFORM_KEY.length());
		}
	}

	void Shader::detectAllStructs(const std::string& shaderSource)
	{
		static const std::string STRUCT_KEY = "struct";

		size_t structLocation = shaderSource.find(STRUCT_KEY);

		while (structLocation != std::string::npos)
		{
			structLocation += STRUCT_KEY.length() + 1; //Ignore the struct keyword and space

			size_t braceOpening = shaderSource.find("{", structLocation);
			size_t braceClosing = shaderSource.find("}", braceOpening);

			std::string name = findShaderStructName(shaderSource.substr(structLocation, braceOpening - structLocation));

			m_nameToStruct[name] = std::make_shared<ShaderStruct>(name, findUniformStructMembers(shaderSource.substr(braceOpening, braceClosing - braceOpening)));

			structLocation = shaderSource.find(STRUCT_KEY, structLocation);
		}
	}

	std::string Shader::findShaderStructName(const std::string& startToOpeningBrace)
	{
		size_t nameEnd = startToOpeningBrace.find(" ");

		std::string possName = startToOpeningBrace;

		if (nameEnd != std::string::npos)
			possName = startToOpeningBrace.substr(0, nameEnd);

		nameEnd = startToOpeningBrace.find("\n");

		if (nameEnd != std::string::npos)
			return possName.substr(0, nameEnd);
		else
			return startToOpeningBrace;
	}

	std::vector<ShaderVariable::SPtr> Shader::findUniformStructMembers(const std::string& openingBraceToClosingBrace)
	{
		std::vector<ShaderVariable::SPtr> returnList;

		static const char charsToIgnore[] = { ' ', '\n', '\t', '{', ';' };
		static const size_t UNSIGNED_NEG_ONE = (size_t)-1;
		static const std::string MEMBER_END = ";";

		size_t memberBegin = 0;
		size_t memberEnd = openingBraceToClosingBrace.find(MEMBER_END);

		while (memberEnd != std::string::npos)
		{
			size_t nameBegin = UNSIGNED_NEG_ONE;
			size_t nameEnd = UNSIGNED_NEG_ONE;

			std::string member = openingBraceToClosingBrace.substr(memberBegin, memberEnd - memberBegin);

			for (unsigned int j = 0; j < member.length(); ++j)
			{
				bool isIgnoreableCharacter = false;

				for (unsigned int k = 0; k < sizeof(charsToIgnore) / sizeof(char); ++k)
				{
					if (member[j] == charsToIgnore[k])
					{
						isIgnoreableCharacter = true;
						break;
					}
				}

				if (nameBegin == UNSIGNED_NEG_ONE && isIgnoreableCharacter == false)
				{
					nameBegin = j;
				}
				else if (nameBegin != UNSIGNED_NEG_ONE && isIgnoreableCharacter)
				{
					nameEnd = j;
					break;
				}
			}

			if (nameBegin != UNSIGNED_NEG_ONE && nameEnd != UNSIGNED_NEG_ONE)
			{
				std::string type = member.substr(nameBegin, nameEnd - nameBegin);

				if (m_nameToStruct.find(type) != m_nameToStruct.end())
				{
					ShaderStruct::SPtr baseStruct = m_nameToStruct[type];

					//Add this structs members.
					for (unsigned int i = 0; i < baseStruct->members.size(); ++i)
						returnList.push_back(std::make_shared<ShaderVariable>(member.substr(nameEnd + 1) + "." + baseStruct->members[i]->getName(), baseStruct->members[i]->getType()));
				}
				else
					returnList.push_back(std::make_shared<ShaderVariable>(member.substr(nameEnd + 1), ShaderVariable::GetShaderVariableType(type)));
			}

			memberBegin = memberEnd;
			memberEnd = openingBraceToClosingBrace.find(MEMBER_END, memberEnd + 1);
		}

		return returnList;
	}
}