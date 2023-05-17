#pragma once

#include "Animation.h"

class MoonWalkAnimation : public Animation
{
public:
	MoonWalkAnimation(Model& model, float speed)
		:Animation(model, speed)
	{
		modelMat = glm::mat4(1.0f);
	}

	void update(const float& deltaTime) override;

private: 
	void setRightLeg(float deltaTime);
	void setLeftLeg(float deltaTime);

	void setRightArm(float deltaTime);
	void setLeftArm(float deltaTime);

private:
	glm::mat4 modelMat;
};