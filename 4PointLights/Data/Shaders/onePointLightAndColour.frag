#version 330

struct BaseLight
{
    vec3 colour;
    float intensity;
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};

struct PointLight
{
    BaseLight base;
	Attenuation attenuation;
    vec3 position;
	float range;
};

in vec4 vertexColour;
in vec3 vertexNormal;
in vec3 vertexWorldPos;

uniform vec4 ambientIntensity;
uniform PointLight DEPointLight1;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
    float diffuseFactor = clamp(dot(normal, direction), 0.0, 1.0);
    vec4 diffuseColor = vec4(base.colour, 1.0) * base.intensity * diffuseFactor;
    
    return diffuseColor;
}

vec4 calcPointLight(PointLight pointLight, vec3 normal)
{
	vec3 lightDirection = vertexWorldPos - pointLight.position;
	float distanceToPoint = length(lightDirection);
	
	if(distanceToPoint > pointLight.range)
		return vec4(0,0,0,0);
	
	lightDirection = normalize(lightDirection);
	
	vec4 color = calcLight(pointLight.base, lightDirection, normal);
	
	float attenuation = pointLight.attenuation.constant +
						pointLight.attenuation.linear * distanceToPoint +
						pointLight.attenuation.exponent * distanceToPoint * distanceToPoint +
						0.0001;
						
	return color / attenuation;
}

void main()
{
	vec3 vNormal = normalize(vertexNormal);
	vec4 lightColour = calcPointLight(DEPointLight1, vNormal);
	
	gl_FragColor = (vertexColour * lightColour) + (vertexColour * ambientIntensity);
}