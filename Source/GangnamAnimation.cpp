#include "GangnamAnimation.h"
#include <GLFW/glfw3.h>

GangnamAnimation::GangnamAnimation(Model& model, float speed)
	: Animation(model, speed)
{
	stage = &stages[0];

	model.componetMap["right_arm"]->transform.set(glm::vec4(-1.0f, 0.2f, -0.05f, glm::radians(150.0f)), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_arm"]->transform.set(glm::vec4(-0.8f, -0.5f, -0.2f, glm::radians(60.0f)), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform.set(glm::vec4(-0.1f, -0.3f, -1.0f, glm::radians(60.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_thigh"]->transform.set(glm::vec4(0.0f, 0.0f, -1.0f, glm::radians(12.0f)), rightThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_thigh"]->transform.set(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(12.0f)), leftThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_knee"]->transform.set(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(12.0f)), rightKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_knee"]->transform.set(glm::vec4(0.0f, 0.0f, -1.0f, glm::radians(12.0f)), leftKneeOffset, glm::vec3(0, 0, 0));
}

void GangnamAnimation::update(const float& deltaTime)
{
	//printf("%d\n", *stage);
	setBodyTrans(deltaTime);
	if (*stage == 0)
	{
		model.componetMap["left_arm"]->transform.set(glm::vec4(-0.8f, -0.5f, -0.2f, glm::radians(60.0f)), leftArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_arm"]->transform.set(glm::vec4(-1.0f, 0.2f, -0.05f, glm::radians(150.0f)), rightArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_forearm"]->transform.set(glm::vec4(-0.1f, -0.3f, -1.0f, glm::radians(60.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_thigh"]->transform.set(glm::vec4(0.0f, 0.0f, -1.0f, glm::radians(12.0f)), rightThighOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_thigh"]->transform.set(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(12.0f)), leftThighOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_knee"]->transform.set(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(12.0f)), rightKneeOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_knee"]->transform.set(glm::vec4(0.0f, 0.0f, -1.0f, glm::radians(12.0f)), leftKneeOffset, glm::vec3(0, 0, 0));
		stage = stages;
	}
	else if (*stage == 10)
	{
		model.componetMap["left_arm"]->transform.set(glm::vec4(-0.9f, 0.25f, -0.36f, glm::radians(45.0f)), leftArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_arm"]->transform.set(glm::vec4(-0.9f, -0.05f, 0.45f, glm::radians(42.0f)), rightArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_forearm"]->transform.set(glm::vec4(0.06f, -0.5f, -0.8f, glm::radians(75.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_forearm"]->transform.set(glm::vec4(-0.22f, 0.96f, -0.18f, glm::radians(112.0f)), rightForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_hand"]->transform.set(glm::vec4(0.12f, -0.8f, 0.6f, glm::radians(112.0f)), leftHandOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_hand"]->transform.set(glm::vec4(-0.1f, -0.25f, -0.96f, glm::radians(42.0f)), rightHandOffset, glm::vec3(0, 0, 0));
		stage++;
	}

	if (*stage < 10)
	{
		if (*stage % 2 == 1)
		{
			setRightThighTrans(deltaTime);
			setRightKneeTrans(deltaTime);
			setRightArmTrans(deltaTime);
			setRightForeArmTrans(deltaTime);
		}
		else
		{
			setLeftThighTrans(deltaTime);
			setLeftKneeTrans(deltaTime);
			setRightArmTrans(deltaTime);
			setRightForeArmTrans(deltaTime);
		}
	}
	else if (*stage > 10)
	{
		if (*stage % 2 == 1)
		{
			setRightThighTrans(deltaTime);
			setRightKneeTrans(deltaTime);
		}
		else
		{
			setLeftThighTrans(deltaTime);
			setLeftKneeTrans(deltaTime);
		}
		setLeftForeArmTrans(deltaTime);
		setRightForeArmTrans(deltaTime);
		setLeftHandTrans(deltaTime);
		setRightHandTrans(deltaTime);
	}

	model.updateTransforms(glm::mat4(1.0f));
}

void GangnamAnimation::setBodyTrans(const float deltaTime)
{
	static int direction = 1;

	float position = model.componetMap["body_base"]->transform.translate.y;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), bodyOffset, glm::vec3(0, position + direction * speed * deltaTime, 0));

	model.componetMap["body_base"]->transform = newTrans;

	if (position < 0.0f && direction == -1)
	{
		direction = 1;
		stage++;
	}
	else if (position > 0.5f && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setRightArmTrans(const float& deltaTime)
{
	float angle = model.componetMap["right_arm"]->transform.rotate.w;
	Transform newTrans(glm::vec4(-1.0f + 0.1f * glm::sin(glfwGetTime() * 6.0f * speed), 0.2f, -0.05f + 0.1f * glm::cos(glfwGetTime() * 6.0f * speed), (angle)), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform = newTrans;
}

void GangnamAnimation::setLeftArmTrans(const float& deltaTime)
{
}

void GangnamAnimation::setRightForeArmTrans(const float& deltaTime)
{
	float angle = model.componetMap["right_forearm"]->transform.rotate.w;
	if (*stage < 9)
	{
		Transform newTrans(glm::vec4(glm::cos(glfwGetTime() * 6.0f * speed), 0.0f, glm::sin(glfwGetTime() * 6.0f * speed), glm::radians(12.0f)), rightForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_forearm"]->transform = newTrans;
	}
	else
	{
		float angle = model.componetMap["right_forearm"]->transform.rotate.w;

		static int direction = 1;

		Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(112.0f), glm::radians(111.0f), glm::vec3(-0.22f, 0.96f, -0.18f), glm::vec3(0.0f, 1.0f, -0.08f)), (angle + direction * speed * deltaTime * 1.0f * 0.0335f)), rightForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_forearm"]->transform = newTrans;

		if (angle < glm::radians(111.0f) && direction == -1)
		{
			direction = 1;
		}
		else if (angle > glm::radians(112.0f) && direction == 1)
		{
			direction = -1;
		}
	}
}

void GangnamAnimation::setLeftForeArmTrans(const float& deltaTime)
{
	float angle = model.componetMap["left_forearm"]->transform.rotate.w;

	static int direction = -1;

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(75.0f), glm::radians(78.0f), glm::vec3(0.06f, -0.5f, -0.8f), glm::vec3(0.3f, -0.3f, -0.9f)), (angle + direction * speed * deltaTime * 3.0f * 0.0335f)), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform = newTrans;

	if (angle < glm::radians(75.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(78.0f) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setRightThighTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["right_thigh"]->transform.rotate.w;

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(12.0f), glm::radians(60.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-0.85f, -0.5f, -0.2f)), (angle + direction * speed * deltaTime * 48.0f * 0.0335f)), rightThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_thigh"]->transform = newTrans;

	if (angle < glm::radians(12.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(60.0f) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setLeftThighTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_thigh"]->transform.rotate.w;

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(12.0f), glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(-0.85f, 0.5f, 0.2f)), (angle + direction * speed * deltaTime * 48.0f * 0.0335f)), leftThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_thigh"]->transform = newTrans;

	if (angle < glm::radians(12.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(60.0f) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setRightKneeTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["right_knee"]->transform.rotate.w;

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(12.0f), glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)), (angle + direction * speed * deltaTime * 48.0f * 0.0335f)), rightKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_knee"]->transform = newTrans;

	if (angle < glm::radians(12.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(60.0f) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setLeftKneeTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_knee"]->transform.rotate.w;

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(12.0f), glm::radians(60.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f, 0.0f, 0.0f)), (angle + direction * speed * deltaTime * 48.0f * 0.0335f)), leftKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_knee"]->transform = newTrans;

	if (angle < glm::radians(12.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(60.0f) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setRightHandTrans(float deltaTime)
{
	float angle = model.componetMap["right_hand"]->transform.rotate.w;

	static int direction = -1;

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(42.0f), glm::radians(14.0f), glm::vec3(-0.1f, -0.25f, -0.96f), glm::vec3(0.0f, -0.2f, -1.0f)), (angle + direction * speed * deltaTime * 28.0f * 0.0335f)), rightHandOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_hand"]->transform = newTrans;

	if (angle < glm::radians(14.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(42.0f) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setLeftHandTrans(float deltaTime)
{
	float angle = model.componetMap["left_hand"]->transform.rotate.w;

	static int direction = -1;

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(112.0f), glm::radians(95.0f), glm::vec3(0.12f, -0.8f, 0.6f), glm::vec3(0.42f, -0.8f, 0.42f)), (angle + direction * speed * deltaTime * 17.0f * 0.0335f)), leftHandOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_hand"]->transform = newTrans;

	if (angle < glm::radians(95.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(112.0f) && direction == 1)
	{
		direction = -1;
	}
}

glm::vec3 GangnamAnimation::rotateAxisWithRange(float angle, float angle_start, float angle_end, glm::vec3 axis_from, glm::vec3 axis_to)
{
	return glm::vec3(axis_from.x + (axis_to.x - axis_from.x) * (angle - angle_start) / (angle_end - angle_start),
		axis_from.y + (axis_to.y - axis_from.y) * (angle - angle_start) / (angle_end - angle_start),
		axis_from.z + (axis_to.z - axis_from.z) * (angle - angle_start) / (angle_end - angle_start));
}
