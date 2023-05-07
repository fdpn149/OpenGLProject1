#include "..\Header\Transform.h"

std::map<std::string, Transform> Transform::trans;

Transform::Transform()
{
	scale = glm::vec3(1.0f);
	rotate = glm::vec4(0, 0, 1.0, glm::radians(0.0f));
	translate = glm::vec3(0);
}

Transform::Transform(glm::vec3 scale, glm::vec4 rotate, glm::vec3 translate)
{
	this->scale = scale;
	this->rotate = rotate;
	this->translate = translate;
}
