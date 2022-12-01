#version 330

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 texCoord;

uniform mat4 DEModelViewProjectionMatrix;

out vec2 vertexTexCoord;

void main()
{
	gl_Position = DEModelViewProjectionMatrix * vec4(vPosition, 1.0);
	vertexTexCoord = texCoord;
}
