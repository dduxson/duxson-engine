#version 330

in vec2 vertexTexCoord;
out vec4 outputColor;

uniform sampler2D DEDiffuse1;

void main()
{
	vec4 vTexColor = texture2D(DEDiffuse1, vertexTexCoord);
	outputColor = (vTexColor.r, vTexColor.r, vTexColor.r, vTexColor.r)*vec4(1.0,0.0,0.0,1.0);
}