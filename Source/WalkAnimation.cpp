#include "WalkAnimation.h"

WalkAnimation::WalkAnimation(Model& model, float speed)
	:Animation(model, speed), rightArmDir(-1), leftArmDir(1), rightThighDir(1), leftThighDir(-1)
{
}

WalkAnimation::~WalkAnimation()
{
	model.componetMap["right_arm"]->transform = Transform();
	model.componetMap["left_arm"]->transform = Transform();
	model.componetMap["right_thigh"]->transform = Transform();
	model.componetMap["left_thigh"]->transform = Transform();
}

void WalkAnimation::update(const float& deltaTime)
{
	// right arm
	setRightArmTrans(deltaTime);
	
	// left arm
	setLeftArmTrans(deltaTime);
	
	// right thigh
	setRightThighTrans(deltaTime);
	
	// left thigh
	setLeftThighTrans(deltaTime);

	model.updateTransforms(glm::mat4(1.0f));
}

void WalkAnimation::rotateComponetByAngle(std::string componet, glm::vec3 offset, float radians)
{
	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, radians), offset, glm::vec3(0, 0, 0));

	model.componetMap[componet]->transform = newTrans;
}

void WalkAnimation::setRightArmTrans(float deltaTime)
{
	std::string componet = "right_arm";
	
	float angle = model.componetMap[componet]->transform.rotate.w;

	rotateComponetByAngle(componet, rightArmOffset, (angle + rightArmDir * speed * deltaTime));

	if (angle < glm::radians(-45.0f) && rightArmDir == -1)
	{
		rightArmDir = 1;
	}
	else if (angle > glm::radians(45.0f) && rightArmDir == 1)
	{
		rightArmDir = -1;
	}
}

void WalkAnimation::setLeftArmTrans(float deltaTime)
{
	std::string componet = "left_arm";

	float angle = model.componetMap[componet]->transform.rotate.w;

	rotateComponetByAngle(componet, leftArmOffset, (angle + leftArmDir * speed * deltaTime));

	if (angle < glm::radians(-45.0f) && leftArmDir == -1)
	{
		leftArmDir = 1;
	}
	else if (angle > glm::radians(45.0f) && leftArmDir == 1)
	{
		leftArmDir = -1;
	}
}

void WalkAnimation::setRightThighTrans(float deltaTime)
{
	std::string componet = "right_thigh";

	float angle = model.componetMap[componet]->transform.rotate.w;

	rotateComponetByAngle(componet, rightThighOffset, (angle + rightThighDir * speed * deltaTime));

	if (angle < glm::radians(-45.0f) && rightThighDir == -1)
	{
		rightThighDir = 1;
	}
	else if (angle > glm::radians(45.0f) && rightThighDir == 1)
	{
		rightThighDir = -1;
	}
}

void WalkAnimation::setLeftThighTrans(float deltaTime)
{
	std::string componet = "left_thigh";

	float angle = model.componetMap[componet]->transform.rotate.w;

	rotateComponetByAngle(componet, leftThighOffset, (angle + leftThighDir * speed * deltaTime));

	if (angle < glm::radians(-45.0f) && leftThighDir == -1)
	{
		leftThighDir = 1;
	}
	else if (angle > glm::radians(45.0f) && leftThighDir == 1)
	{
		leftThighDir = -1;
	}
}
