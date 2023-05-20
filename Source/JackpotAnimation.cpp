#include "JackpotAnimation.h"
#include <iostream>

const float MAX_JUMP_HEIGHT = 0.5f;

JackpotAnimation::JackpotAnimation(Model& model, float speed)
	:Animation(model, speed), 
	jumpHeight(0.0f),
	rightForeArmDir(-1)
{
	// init right arm
	Transform trans(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(10.0f)), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform = trans;
	
	// init left arm
	trans = Transform(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(-10.0f)), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_arm"]->transform = trans;

	// init right forearm
	trans = Transform(glm::vec4(0.3f, 0.6f, -0.3f, 0.0f), rightForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_forearm"]->transform = trans;

	// init left forearm
	trans = Transform(glm::vec4(-0.3f, 0.6f, -0.3f, 0.0f), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform = trans;

	// init right thigh
	trans = Transform(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(5.0f)), rightThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_thigh"]->transform = trans;

	// init left thigh
	trans = Transform(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(-5.0f)), leftThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_thigh"]->transform = trans;
}

JackpotAnimation::~JackpotAnimation()
{
	model.componetMap["right_arm"]->transform = Transform();
	model.componetMap["left_arm"]->transform = Transform();
	model.componetMap["right_forearm"]->transform = Transform();
	model.componetMap["left_forearm"]->transform = Transform();
	model.componetMap["right_thigh"]->transform = Transform();
	model.componetMap["left_thigh"]->transform = Transform();
}

void JackpotAnimation::update(const float& deltaTime)
{
	setRightArmTrans(deltaTime);
	setLeftArmTrans(deltaTime);
	setRightForeArmTrans(deltaTime);
	setLeftForeArmTrans(deltaTime);
	setRightThighTrans(deltaTime);
	setLeftThighTrans(deltaTime);
	
	model.updateTransforms(getModel(deltaTime));
}

glm::mat4 JackpotAnimation::getModel(float deltaTime)
{
	glm::mat4 model(1.0f);

	jumpHeight -= rightForeArmDir * speed * deltaTime * (MAX_JUMP_HEIGHT / glm::radians(180.0f));

	return glm::translate(model, glm::vec3(0.0f, jumpHeight, 0.0f));
}

void JackpotAnimation::setRightArmTrans(float deltaTime)
{
	float angle = model.componetMap["right_arm"]->transform.rotate.w;

	float newAngle = angle + rightForeArmDir * speed * deltaTime * (170.0f / 180.0f);

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, newAngle), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform = newTrans;
}

void JackpotAnimation::setLeftArmTrans(float deltaTime)
{
	float angle = model.componetMap["left_arm"]->transform.rotate.w;

	float newAngle = angle - rightForeArmDir * speed * deltaTime * (170.0f / 180.0f);

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, newAngle), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_arm"]->transform = newTrans;
}

void JackpotAnimation::setRightForeArmTrans(float deltaTime)
{
	float angle = model.componetMap["right_forearm"]->transform.rotate.w;

	float newAngle = angle + rightForeArmDir * speed * deltaTime;

	Transform newTrans(glm::vec4(0.3f, 0.6f, -0.3f, newAngle), rightForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_forearm"]->transform = newTrans;

	if (angle < glm::radians(-180.0f) && rightForeArmDir == -1)
	{
		rightForeArmDir = 1;
	}
	else if (angle > glm::radians(0.0f) && rightForeArmDir == 1)
	{
		rightForeArmDir = -1;
	}
}

void JackpotAnimation::setLeftForeArmTrans(float deltaTime)
{
	float angle = model.componetMap["left_forearm"]->transform.rotate.w;

	float newAngle = angle - rightForeArmDir * speed * deltaTime;

	Transform newTrans(glm::vec4(-0.3f, 0.6f, -0.3f, newAngle), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform = newTrans;
}

void JackpotAnimation::setRightThighTrans(float deltaTime)
{
	float angle = model.componetMap["right_thigh"]->transform.rotate.w;

	float newAngle = angle + rightForeArmDir * speed * deltaTime * (35.0f / 180.0f);

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, newAngle), rightThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_thigh"]->transform = newTrans;
}

void JackpotAnimation::setLeftThighTrans(float deltaTime)
{
	float angle = model.componetMap["left_thigh"]->transform.rotate.w;

	float newAngle = angle - rightForeArmDir * speed * deltaTime * (35.0f / 180.0f);

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, newAngle), leftThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_thigh"]->transform = newTrans;
}
