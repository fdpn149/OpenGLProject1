#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 pos;
	vec3 color;
};

uniform Material material;
uniform Light light;

uniform vec3 cameraPos;

void main()
{
	vec3 ambient = material.diffuse * light.color * material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.pos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.color * material.diffuse;

	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.color * spec * material.specular;
	vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}