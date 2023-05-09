#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"

class Material
{
public:
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	float shininess = 64.0f;
	Material();
	Material(glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _ambient, float _shininess);
};

