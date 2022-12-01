/*!********************************************************************
* File:	ShaderVariableMap.h
*
* \brief	Class used to keep track of the variables that should be
*			in the shaders.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include <string>
#include <map>
#include <glm/glm.hpp>
#include "ShaderVariable.h"

namespace DE
{
	class ShaderVariableMap
	{
		public:
			ShaderVariableMap();

			virtual ~ShaderVariableMap();

			void set(const std::string& name, const float floatData);
			void set(const std::string& name, const int intData);
			void set(const std::string& name, const unsigned int uintData);
			void set(const std::string& name, const glm::vec2 &vec2Data);
			void set(const std::string& name, const glm::vec3 &vec3Data);
			void set(const std::string& name, const glm::vec4 &vec4Data);
			void set(const std::string& name, const glm::mat2 &mat2Data);
			void set(const std::string& name, const glm::mat3 &mat3Data);
			void set(const std::string& name, const glm::mat4 &mat4Data);

			float getFloat(const std::string& name) const;
			int getInt(const std::string& name) const;
			unsigned int getUInt(const std::string& name) const;
			glm::vec2 getVec2(const std::string& name) const;
			glm::vec3 getVec3(const std::string& name) const;
			glm::vec4 getVec4(const std::string& name) const;
			glm::mat2 getMat2(const std::string& name) const;
			glm::mat3 getMat3(const std::string& name) const;
			glm::mat4 getMat4(const std::string& name) const;

		private:
			std::map<std::string, int> m_nameToInt;
			std::map<std::string, float> m_nameToFloat;
			std::map<std::string, unsigned int> m_nameToUInt;
			std::map<std::string, glm::vec2> m_nameToVec2;
			std::map<std::string, glm::vec3> m_nameToVec3;
			std::map<std::string, glm::vec4> m_nameToVec4;
			std::map<std::string, glm::mat2> m_nameToMat2;
			std::map<std::string, glm::mat3> m_nameToMat3;
			std::map<std::string, glm::mat4> m_nameToMat4;
		};
}