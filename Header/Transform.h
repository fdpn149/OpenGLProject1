#pragma once
#include <glm/glm.hpp>
#include <string>
#include <map>
#include <vector>

class Transform
{
public:
	glm::vec4 rotate;
	glm::vec3 offset;
	glm::vec3 translate;

	Transform();
	Transform(glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate);

	void set(glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate);
};

