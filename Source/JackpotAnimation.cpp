#include "JackpotAnimation.h"

void JackpotAnimation::Update(float deltaTime)
{
	setRightArmTrans(deltaTime);
	setLeftArmTrans(deltaTime);
	setRightForeArmTrans(deltaTime);
	setLeftForeArmTrans(deltaTime);
	setRightThighTrans(deltaTime);
	setLeftThighTrans(deltaTime);
}

void JackpotAnimation::setRightArmTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["right_arm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, (angle + direction * speed * deltaTime)), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform = newTrans;

	if (angle < glm::radians(-130.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(10.0f) && direction == 1)
	{
		direction = -1;
	}
}

void JackpotAnimation::setLeftArmTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_arm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, (angle + direction * speed * deltaTime)), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_arm"]->transform = newTrans;

	if (angle < glm::radians(-10.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(130.0f) && direction == 1)
	{
		direction = -1;
	}
}

void JackpotAnimation::setRightForeArmTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["right_forearm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(2.0f, 3.0f, 1.0f, (angle + direction * speed * deltaTime * 0.32)), rightForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_forearm"]->transform = newTrans;

	if (angle < glm::radians(-45.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(0.0f) && direction == 1)
	{
		direction = -1;
	}
}

void JackpotAnimation::setLeftForeArmTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_forearm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(-2.0f, 3.0f, 1.0f, (angle + direction * speed * deltaTime * 0.32)), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform = newTrans;

	if (angle < glm::radians(0.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(45.0f) && direction == 1)
	{
		direction = -1;
	}
}

void JackpotAnimation::setRightThighTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["right_thigh"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, (angle + direction * speed * deltaTime * 0.25)), rightThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_thigh"]->transform = newTrans;

	if (angle < glm::radians(-30.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(5.0f) && direction == 1)
	{
		direction = -1;
	}
}

void JackpotAnimation::setLeftThighTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_thigh"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, (angle + direction * speed * deltaTime * 0.25)), leftThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_thigh"]->transform = newTrans;

	if (angle < glm::radians(-5.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(30.0f) && direction == 1)
	{
		direction = -1;
	}
}
