#include "WalkAnimation.h"

void WalkAnimation::Update(float deltaTime)
{
	// right arm
	setRightArmTrans(deltaTime);
	
	// left arm
	setLeftArmTrans(deltaTime);
	
	// right thigh
	setRightThighTrans(deltaTime);
	
	// left thigh
	setLeftThighTrans(deltaTime);
}

void WalkAnimation::rotateComponetByAngle(std::string componet, glm::vec3 offset, float radians)
{
	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, radians), offset, glm::vec3(0, 0, 0));

	model.componetMap[componet]->transform = newTrans;
}

void WalkAnimation::setRightArmTrans(float deltaTime)
{
	static int direction = -1;

	std::string componet = "right_arm";
	
	float angle = model.componetMap[componet]->transform.rotate.w;

	rotateComponetByAngle(componet, rightArmOffset, (angle + direction * speed * deltaTime));

	if (angle < glm::radians(-45.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(45.0f) && direction == 1)
	{
		direction = -1;
	}
}

void WalkAnimation::setLeftArmTrans(float deltaTime)
{
	static int direction = 1;

	std::string componet = "left_arm";

	float angle = model.componetMap[componet]->transform.rotate.w;

	rotateComponetByAngle(componet, leftArmOffset, (angle + direction * speed * deltaTime));

	if (angle < glm::radians(-45.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(45.0f) && direction == 1)
	{
		direction = -1;
	}
}

void WalkAnimation::setRightThighTrans(float deltaTime)
{
	static int direction = 1;

	std::string componet = "right_thigh";

	float angle = model.componetMap[componet]->transform.rotate.w;

	rotateComponetByAngle(componet, rightThighOffset, (angle + direction * speed * deltaTime));

	if (angle < glm::radians(-45.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(45.0f) && direction == 1)
	{
		direction = -1;
	}
}

void WalkAnimation::setLeftThighTrans(float deltaTime)
{
	static int direction = -1;

	std::string componet = "left_thigh";

	float angle = model.componetMap[componet]->transform.rotate.w;

	rotateComponetByAngle(componet, leftThighOffset, (angle + direction * speed * deltaTime));

	if (angle < glm::radians(-45.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(45.0f) && direction == 1)
	{
		direction = -1;
	}
}
