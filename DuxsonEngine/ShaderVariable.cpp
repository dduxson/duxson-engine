#include "./Include/ShaderVariable.h"
#include <algorithm>

using namespace DE;

ShaderVariable::ShaderVariableType ShaderVariable::GetShaderVariableType(const std::string& type)
{
	if (type.compare("float") == 0)
		return eFloat;
	else if (type.compare("int") == 0)
		return eInt;
	else if (type.compare("uint") == 0)
		return eUnsignedInt;
	else if (type.compare("vec2") == 0)
		return eVec2;
	else if (type.compare("vec3") == 0)
		return eVec3;
	else if (type.compare("vec4") == 0)
		return eVec4;
	else if (type.compare("mat2") == 0)
		return eMat2;
	else if (type.compare("mat3") == 0)
		return eMat3;
	else if (type.compare("mat4") == 0)
		return eMat4;
	else if (type.compare("sampler2D") == 0)
		return eSampler;
	else
		return eInvalid;
}