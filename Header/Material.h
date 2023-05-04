#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

class Material
{
public:
	Shader* shader;
	unsigned int diffuse;
	unsigned specular;
	glm::vec3 ambient;
	float shininess;
	Material(Shader* _shader, unsigned _diffuse, unsigned _specular, glm::vec3 _ambient, float _shininess);
};

