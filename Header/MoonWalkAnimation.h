#pragma once

#include "Animation.h"

class MoonWalkAnimation : public Animation
{
public:
	MoonWalkAnimation(Model& model, float speed);

	~MoonWalkAnimation();

	void update(const float& deltaTime) override;

private: 
	void setRightLeg(float deltaTime);
	void setLeftLeg(float deltaTime);

	void setRightArm(float deltaTime);
	void setLeftArm(float deltaTime);

private:
	glm::mat4 modelMat;

	int rightArmDir;
	int leftArmDir;
	int rightLegDir;
	int leftLegDir;
};