#version 330

in vec2 vertexTexCoord;

uniform sampler2D DEDiffuse1;

void main()
{
	gl_FragColor = texture2D(DEDiffuse1, vertexTexCoord);
}