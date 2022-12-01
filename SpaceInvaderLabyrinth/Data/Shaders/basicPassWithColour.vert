#version 330

layout(location = 0) in vec3 vPosition;
layout(location = 4) in vec4 colour;

uniform mat4 DEModelViewProjectionMatrix;

out vec4 vertexColour;

void main()
{
	gl_Position = DEModelViewProjectionMatrix * vec4(vPosition, 1.0);
	vertexColour = colour;
}
