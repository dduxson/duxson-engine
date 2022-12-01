#version 330

layout(location = 0) in vec3 vPosition;
layout(location = 2) in vec3 normal;
layout(location = 4) in vec4 colour;

uniform mat4 DEModelViewProjectionMatrix;
uniform mat3 DENormalMatrix;

out vec4 vertexColour;
out vec3 vertexNormal;

void main()
{
	gl_Position = DEModelViewProjectionMatrix * vec4(vPosition, 1.0);
	vertexColour = colour;
	vertexNormal = DENormalMatrix * normal;
}
