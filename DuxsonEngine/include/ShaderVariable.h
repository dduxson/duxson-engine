/*!********************************************************************
* File:	ShaderVariable.h
*
* \brief	Class used to represent a variable inside a shader for 
*			easy storage and manipulation.
*
* \author	David Duxson
*
* \date	04/03/2015
*
**********************************************************************/
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

namespace DE
{
	class ShaderVariable
	{
		public:
			typedef std::shared_ptr<ShaderVariable> SPtr;

			enum ShaderVariableType
			{
				eInvalid = -1,
				eFloat = 0,
				eInt,
				eUnsignedInt,
				eVec2,
				eVec3,
				eVec4,
				eMat2,
				eMat3,
				eMat4,
				eSampler,
			};

		public:
			ShaderVariable(const std::string& name, ShaderVariableType type)
				:m_name(name), m_type(type) {};

			virtual ~ShaderVariable() {};

			const std::string& getName() const { return m_name; }
			ShaderVariableType getType() const { return m_type; }

			static ShaderVariableType GetShaderVariableType(const std::string& type);

		private:
			std::string	m_name;
			ShaderVariableType	m_type;
	};
}