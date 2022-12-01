#version 330

struct BaseLight
{
    vec3 colour;
    float intensity;
};

struct DirectionalLight
{
    BaseLight base;
    vec3 direction;
};

in vec4 vertexColour;
in vec3 vertexNormal;

uniform vec4 ambientIntensity;
uniform DirectionalLight DEDirectionalLight1;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
    float diffuseFactor = clamp(dot(normal, direction), 0.0, 1.0);
    vec4 diffuseColor = vec4(base.colour, 1.0) * base.intensity * diffuseFactor;
    
    return diffuseColor;
}

void main()
{
	vec3 vNormal = normalize(vertexNormal);
	vec4 lightColour = calcLight(DEDirectionalLight1.base, normalize(DEDirectionalLight1.direction), vNormal);
	
	gl_FragColor = (vertexColour * lightColour) + (vertexColour * ambientIntensity);
}