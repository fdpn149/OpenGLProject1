#pragma once

#include "Model.h"

class Animation
{
public:
	Animation(Model& model, float speed);


	virtual void update(const float& deltaTime) = 0;


protected:
	Model& model;

	int stage;

	float speed;
	glm::vec3 bodyOffset;

	glm::vec3 waistBaseOffset;

	glm::vec3 rightArmOffset;
	glm::vec3 leftArmOffset;

	glm::vec3 rightThighOffset;
	glm::vec3 leftThighOffset;

	glm::vec3 rightForeArmOffset;
	glm::vec3 leftForeArmOffset;

	glm::vec3 rightKneeOffset;
	glm::vec3 leftKneeOffset;

	glm::vec3 rightFootOffset;
	glm::vec3 leftFootOffset;
};

