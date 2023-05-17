#include "MoonWalkAnimation.h"

void MoonWalkAnimation::update(const float& deltaTime)
{
	setRightLeg(deltaTime);
	setLeftLeg(deltaTime);
	setRightArm(deltaTime);
	setLeftArm(deltaTime);


	
	modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -deltaTime * speed));
	model.updateTransforms(modelMat);
}

void MoonWalkAnimation::setRightLeg(float deltaTime)
{
	static int direction = -1;
	
	// set thigh trans
	float thighAngle = model.componetMap["right_thigh"]->transform.rotate.w;

	Transform thighTrans(glm::vec4(1.0f, 0.0f, 0.0f, (thighAngle + direction * speed * deltaTime)), rightThighOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_thigh"]->transform = thighTrans;
	
	// set knee trans
	float kneeAngle = model.componetMap["right_knee"]->transform.rotate.w;
	if (kneeAngle < glm::radians(45.0f) && direction == -1
		|| kneeAngle > glm::radians(0.0f) && direction == 1)
	{
		Transform kneeTrans(glm::vec4(1.0f, 0.0f, 0.0f, (kneeAngle + (-direction) * speed * deltaTime * 3.0f)), rightKneeOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_knee"]->transform = kneeTrans;
	}
	

	if (thighAngle < glm::radians(-45.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (thighAngle > glm::radians(30.0f) && direction == 1)
	{
		direction = -1;
	}
}

void MoonWalkAnimation::setLeftLeg(float deltaTime)
{
	static int direction = 1;

	// set thigh trans
	float thighAngle = model.componetMap["left_thigh"]->transform.rotate.w;

	Transform thighTrans(glm::vec4(1.0f, 0.0f, 0.0f, (thighAngle + direction * speed * deltaTime)), rightThighOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_thigh"]->transform = thighTrans;

	// set knee trans
	float kneeAngle = model.componetMap["left_knee"]->transform.rotate.w;
	if (kneeAngle < glm::radians(45.0f) && direction == -1
		|| kneeAngle > glm::radians(0.0f) && direction == 1)
	{
		Transform kneeTrans(glm::vec4(1.0f, 0.0f, 0.0f, (kneeAngle + (-direction) * speed * deltaTime * 3.0f)), rightKneeOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_knee"]->transform = kneeTrans;
	}


	if (thighAngle < glm::radians(-45.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (thighAngle > glm::radians(30.0f) && direction == 1)
	{
		direction = -1;
	}
}

void MoonWalkAnimation::setRightArm(float deltaTime)
{
	static int direction = 1;

	// set arm trans
	float armAngel = model.componetMap["right_arm"]->transform.rotate.w;

	Transform armTrans(glm::vec4(1.0f, 0.0f, 0.0f, (armAngel + direction * speed * deltaTime)), rightArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_arm"]->transform = armTrans;

	// set forearm trans
	float forearmAngle = model.componetMap["right_forearm"]->transform.rotate.w;
	if (forearmAngle < glm::radians(45.0f) && direction == -1
		|| forearmAngle > glm::radians(10.0f) && direction == 1)
	{
		Transform kneeTrans(glm::vec4(1.0f, 0.0f, 0.0f, (forearmAngle + (-direction) * speed * deltaTime * 3.0f)), rightForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_forearm"]->transform = kneeTrans;
	}


	if (armAngel < glm::radians(-45.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (armAngel > glm::radians(30.0f) && direction == 1)
	{
		direction = -1;
	}
}

void MoonWalkAnimation::setLeftArm(float deltaTime)
{
	static int direction = -1;

	// set arm trans
	float armAngel = model.componetMap["left_arm"]->transform.rotate.w;

	Transform armTrans(glm::vec4(1.0f, 0.0f, 0.0f, (armAngel + direction * speed * deltaTime)), leftArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_arm"]->transform = armTrans;

	// set forearm trans
	float forearmAngle = model.componetMap["left_forearm"]->transform.rotate.w;
	if (forearmAngle < glm::radians(45.0f) && direction == -1
		|| forearmAngle > glm::radians(10.0f) && direction == 1)
	{
		Transform kneeTrans(glm::vec4(1.0f, 0.0f, 0.0f, (forearmAngle + (-direction) * speed * deltaTime * 3.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_forearm"]->transform = kneeTrans;
	}


	if (armAngel < glm::radians(-45.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (armAngel > glm::radians(30.0f) && direction == 1)
	{
		direction = -1;
	}
}
