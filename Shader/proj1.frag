#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

struct Material
{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
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
	vec3 ambient = texture(material.diffuse, TexCoord).rgb * light.color * material.ambient;

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.pos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.color * (texture(material.diffuse, TexCoord).rgb);

	vec3 viewDir = normalize(cameraPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.color * (spec * texture(material.specular, TexCoord).rgb);
	vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
}