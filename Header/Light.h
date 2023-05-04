#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class Light
{
public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;
	Light(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color);
private:
	void UpdateDirection();
};

