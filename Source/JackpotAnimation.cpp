#include "JackpotAnimation.h"
#include <iostream>

const float MAX_JUMP_HEIGHT = 0.5f;

JackpotAnimation::JackpotAnimation(Model& model, float speed)
	:Animation(model, speed)
{
	jumpHeight = 0.0f;

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
	static int direction = 1;

	glm::mat4 model(1.0f);

	jumpHeight += direction * speed * deltaTime * (MAX_JUMP_HEIGHT / glm::radians(180.0f));

	if (jumpHeight > MAX_JUMP_HEIGHT)
	{
		direction = -1;
	}
	else if(jumpHeight < 0)
	{
		direction = 1;
	}

	model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));

	return glm::translate(model, glm::vec3(0.0f, jumpHeight, 0.0f));
}

void JackpotAnimation::setRightArmTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["right_arm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, (angle + direction * speed * deltaTime * 0.944f)), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform = newTrans;

	if (angle < glm::radians(-160.0f) && direction == -1)
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

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, (angle + direction * speed * deltaTime * 0.944f)), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_arm"]->transform = newTrans;

	if (angle < glm::radians(-10.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(160.0f) && direction == 1)
	{
		direction = -1;
	}
}

void JackpotAnimation::setRightForeArmTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["right_forearm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.3f, 0.6f, -0.3f, (angle + direction * speed * deltaTime)), rightForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_forearm"]->transform = newTrans;

	if (angle < glm::radians(-180.0f) && direction == -1)
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

	Transform newTrans(glm::vec4(-0.3f, 0.6f, -0.3f, (angle + direction * speed * deltaTime)), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform = newTrans;

	if (angle < glm::radians(0.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(180.0f) && direction == 1)
	{
		direction = -1;
	}
}

void JackpotAnimation::setRightThighTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["right_thigh"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, (angle + direction * speed * deltaTime * 0.194f)), rightThighOffset, glm::vec3(0, 0, 0));
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

	Transform newTrans(glm::vec4(0.0f, 0.0f, 1.0f, (angle + direction * speed * deltaTime * 0.194f)), leftThighOffset, glm::vec3(0, 0, 0));
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
