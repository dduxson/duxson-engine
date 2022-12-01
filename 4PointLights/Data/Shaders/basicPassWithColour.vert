#version 330

layout(location = 0) in vec3 vPosition;
layout(location = 2) in vec3 normal;
layout(location = 4) in vec4 colour;

uniform mat4 DEModelViewProjectionMatrix;
uniform mat4 DEModelMatrix;
uniform mat3 DENormalMatrix;

out vec4 vertexColour;
out vec3 vertexNormal;
out vec3 vertexWorldPos;

void main()
{
	gl_Position = DEModelViewProjectionMatrix * vec4(vPosition, 1.0);
	vertexWorldPos = vec4(vPosition, 1.0).xyz;
	vertexColour = colour;
	vertexNormal = DENormalMatrix * normal;
}
