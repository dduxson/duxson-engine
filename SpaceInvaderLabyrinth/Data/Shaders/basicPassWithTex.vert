#version 330

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 DEModelViewProjectionMatrix;
uniform mat3 DENormalMatrix;

out vec2 vertexTexCoord;
out vec3 vertexNormal;

void main()
{
	gl_Position = DEModelViewProjectionMatrix * vec4(vPosition, 1.0);
	vertexTexCoord = texCoord;
	vertexNormal = DENormalMatrix * normal;
}
