#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"

#include <iostream>

Transform::Transform()
{
	rotate = glm::vec4(0, 0, 1.0, glm::radians(0.0f));
	offset = glm::vec3(0);
	translate = glm::vec3(0);
}

Transform::Transform(glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate)
{
	this->rotate = rotate;
	this->offset = offset;
	this->translate = translate;
}

void Transform::set(glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate)
{
	this->rotate = rotate;
	this->offset = offset;
	this->translate = translate;
}