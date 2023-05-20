#include "MoonWalkAnimation.h"

MoonWalkAnimation::MoonWalkAnimation(Model& model, float speed)
	:Animation(model, speed),
	modelMat(glm::mat4(1.0f)),
	rightArmDir(1),
	leftArmDir(-1),
	rightLegDir(-1),
	leftLegDir(1)
{
}

MoonWalkAnimation::~MoonWalkAnimation()
{
	model.componetMap["right_arm"]->transform = Transform();
	model.componetMap["left_arm"]->transform = Transform();
	model.componetMap["right_forearm"]->transform = Transform();
	model.componetMap["left_forearm"]->transform = Transform();
	model.componetMap["right_thigh"]->transform = Transform();
	model.componetMap["left_thigh"]->transform = Transform();
	model.componetMap["right_knee"]->transform = Transform();
	model.componetMap["left_knee"]->transform = Transform();
}

void MoonWalkAnimation::update(const float& deltaTime)
{
	setRightLeg(deltaTime);
	setLeftLeg(deltaTime);
	setRightArm(deltaTime);
	setLeftArm(deltaTime);
	
	/*modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -deltaTime * speed));*/
	model.updateTransforms(modelMat);
}

void MoonWalkAnimation::setRightLeg(float deltaTime)
{	
	// set thigh trans
	float thighAngle = model.componetMap["right_thigh"]->transform.rotate.w;

	float newThighAngle = thighAngle + rightLegDir * speed * deltaTime;

	Transform thighTrans(glm::vec4(1.0f, 0.0f, 0.0f, newThighAngle), rightThighOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_thigh"]->transform = thighTrans;
	
	// set knee trans
	float kneeAngle = model.componetMap["right_knee"]->transform.rotate.w;

	if (kneeAngle < glm::radians(45.0f) && rightLegDir == -1
		|| kneeAngle > glm::radians(0.0f) && rightLegDir == 1)
	{
		float newKneeAngle = kneeAngle + (-rightLegDir) * speed * deltaTime * 3.0f;

		Transform kneeTrans(glm::vec4(1.0f, 0.0f, 0.0f, newKneeAngle), rightKneeOffset, glm::vec3(0, 0, 0));

		model.componetMap["right_knee"]->transform = kneeTrans;
	}


	if (thighAngle < glm::radians(-45.0f) && rightLegDir == -1)
	{
		rightLegDir = 1;
	}
	else if (thighAngle > glm::radians(30.0f) && rightLegDir == 1)
	{
		rightLegDir = -1;
	}
}

void MoonWalkAnimation::setLeftLeg(float deltaTime)
{
	// set thigh trans
	float thighAngle = model.componetMap["left_thigh"]->transform.rotate.w;

	float newThighAngle = thighAngle + leftLegDir * speed * deltaTime;

	Transform thighTrans(glm::vec4(1.0f, 0.0f, 0.0f, newThighAngle), rightThighOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_thigh"]->transform = thighTrans;

	// set knee trans
	float kneeAngle = model.componetMap["left_knee"]->transform.rotate.w;
	if (kneeAngle < glm::radians(45.0f) && leftLegDir == -1
		|| kneeAngle > glm::radians(0.0f) && leftLegDir == 1)
	{
		float newKneeAngle = kneeAngle + (-leftLegDir) * speed * deltaTime * 3.0f;

		Transform kneeTrans(glm::vec4(1.0f, 0.0f, 0.0f, newKneeAngle), rightKneeOffset, glm::vec3(0, 0, 0));

		model.componetMap["left_knee"]->transform = kneeTrans;
	}


	if (thighAngle < glm::radians(-45.0f) && leftLegDir == -1)
	{
		leftLegDir = 1;
	}
	else if (thighAngle > glm::radians(30.0f) && leftLegDir == 1)
	{
		leftLegDir = -1;
	}
}

void MoonWalkAnimation::setRightArm(float deltaTime)
{
	// set arm trans
	float armAngel = model.componetMap["right_arm"]->transform.rotate.w;

	float newArmAngle = armAngel + rightArmDir * speed * deltaTime;

	Transform armTrans(glm::vec4(1.0f, 0.0f, 0.0f, newArmAngle), rightArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_arm"]->transform = armTrans;

	// set forearm trans
	float forearmAngle = model.componetMap["right_forearm"]->transform.rotate.w;
	if (forearmAngle < glm::radians(45.0f) && rightArmDir == -1
		|| forearmAngle > glm::radians(10.0f) && rightArmDir == 1)
	{
		float newforearmAngle = forearmAngle + (-rightArmDir) * speed * deltaTime * 3.0f;

		Transform forearmTrans(glm::vec4(1.0f, 0.0f, 0.0f, newforearmAngle), rightForeArmOffset, glm::vec3(0, 0, 0));

		model.componetMap["right_forearm"]->transform = forearmTrans;
	}


	if (armAngel < glm::radians(-45.0f) && rightArmDir == -1)
	{
		rightArmDir = 1;
	}
	else if (armAngel > glm::radians(30.0f) && rightArmDir == 1)
	{
		rightArmDir = -1;
	}
}

void MoonWalkAnimation::setLeftArm(float deltaTime)
{
	// set arm trans
	float armAngel = model.componetMap["left_arm"]->transform.rotate.w;

	float newArmAngle = armAngel + leftArmDir * speed * deltaTime;

	Transform armTrans(glm::vec4(1.0f, 0.0f, 0.0f, newArmAngle), leftArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_arm"]->transform = armTrans;

	// set forearm trans
	float forearmAngle = model.componetMap["left_forearm"]->transform.rotate.w;
	if (forearmAngle < glm::radians(45.0f) && leftArmDir == -1
		|| forearmAngle > glm::radians(10.0f) && leftArmDir == 1)
	{
		float newForearmAngle = forearmAngle + (-leftArmDir) * speed * deltaTime * 3.0f;

		Transform forearmTrans(glm::vec4(1.0f, 0.0f, 0.0f, newForearmAngle), leftForeArmOffset, glm::vec3(0, 0, 0));

		model.componetMap["left_forearm"]->transform = forearmTrans;
	}


	if (armAngel < glm::radians(-45.0f) && leftArmDir == -1)
	{
		leftArmDir = 1;
	}
	else if (armAngel > glm::radians(30.0f) && leftArmDir == 1)
	{
		leftArmDir = -1;
	}
}
