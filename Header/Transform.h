#pragma once
#include <glm/glm.hpp>
#include <string>
#include <map>
class Transform
{
public:
	glm::vec3 scale;
	glm::vec4 rotate;
	glm::vec3 translate;

	static std::map<std::string, Transform> trans;

	Transform();
	Transform(glm::vec3 scale, glm::vec4 rotate, glm::vec3 translate);
};

