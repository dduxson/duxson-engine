#include "./Include/ShaderVariableMap.h"

namespace DE
{
	ShaderVariableMap::ShaderVariableMap()
	{

	}

	ShaderVariableMap::~ShaderVariableMap()
	{

	}

	void ShaderVariableMap::set(const std::string& name, const float floatData)
	{
		m_nameToFloat[name] = floatData;
	}

	void ShaderVariableMap::set(const std::string& name, const int intData)
	{
		m_nameToInt[name] = intData;
	}

	void ShaderVariableMap::set(const std::string& name, const unsigned int uintData)
	{
		m_nameToUInt[name] = uintData;
	}

	void ShaderVariableMap::set(const std::string& name, const glm::vec2 &vec2Data)
	{
		m_nameToVec2[name] = vec2Data;
	}

	void ShaderVariableMap::set(const std::string& name, const glm::vec3 &vec3Data)
	{
		m_nameToVec3[name] = vec3Data;
	}

	void ShaderVariableMap::set(const std::string& name, const glm::vec4 &vec4Data)
	{
		m_nameToVec4[name] = vec4Data;
	}

	void ShaderVariableMap::set(const std::string& name, const glm::mat2 &mat2Data)
	{
		m_nameToMat2[name] = mat2Data;
	}

	void ShaderVariableMap::set(const std::string& name, const glm::mat3 &mat3Data)
	{
		m_nameToMat3[name] = mat3Data;
	}

	void ShaderVariableMap::set(const std::string& name, const glm::mat4 &mat4Data)
	{
		m_nameToMat4[name] = mat4Data;
	}

	float ShaderVariableMap::getFloat(const std::string& name) const
	{
		std::map<std::string, float>::const_iterator it = m_nameToFloat.find(name);

		if (it != m_nameToFloat.end())
			return it->second;
		else
			return 0.0f;
	}

	int ShaderVariableMap::getInt(const std::string& name) const
	{
		std::map<std::string, int>::const_iterator it = m_nameToInt.find(name);

		if (it != m_nameToInt.end())
			return it->second;
		else
			return 0;
	}

	unsigned int ShaderVariableMap::getUInt(const std::string& name) const
	{
		std::map<std::string, unsigned int>::const_iterator it = m_nameToUInt.find(name);

		if (it != m_nameToUInt.end())
			return it->second;
		else
			return 0;
	}

	glm::vec2 ShaderVariableMap::getVec2(const std::string& name) const
	{
		std::map<std::string, glm::vec2>::const_iterator it = m_nameToVec2.find(name);

		if (it != m_nameToVec2.end())
			return it->second;
		else
			return glm::vec2();
	}

	glm::vec3 ShaderVariableMap::getVec3(const std::string& name) const
	{
		std::map<std::string, glm::vec3>::const_iterator it = m_nameToVec3.find(name);

		if (it != m_nameToVec3.end())
			return it->second;
		else
			return glm::vec3();
	}

	glm::vec4 ShaderVariableMap::getVec4(const std::string& name) const
	{
		std::map<std::string, glm::vec4>::const_iterator it = m_nameToVec4.find(name);

		if (it != m_nameToVec4.end())
			return it->second;
		else
			return glm::vec4();
	}

	glm::mat2 ShaderVariableMap::getMat2(const std::string& name) const
	{
		std::map<std::string, glm::mat2>::const_iterator it = m_nameToMat2.find(name);

		if (it != m_nameToMat2.end())
			return it->second;
		else
			return glm::mat2();
	}

	glm::mat3 ShaderVariableMap::getMat3(const std::string& name) const
	{
		std::map<std::string, glm::mat3>::const_iterator it = m_nameToMat3.find(name);

		if (it != m_nameToMat3.end())
			return it->second;
		else
			return glm::mat3();
	}

	glm::mat4 ShaderVariableMap::getMat4(const std::string& name) const
	{
		std::map<std::string, glm::mat4>::const_iterator it = m_nameToMat4.find(name);

		if (it != m_nameToMat4.end())
			return it->second;
		else
			return glm::mat4();
	}
}