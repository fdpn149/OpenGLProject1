#include "GangnamAnimation.h"
#include <GLFW/glfw3.h>

GangnamAnimation::GangnamAnimation(Model& model, float speed)
	: Animation(model, speed)
{
	stage = stages;

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
		model.componetMap["right_arm"]->transform.set(glm::vec4(-1.0f, 0.2f, -0.05f, glm::radians(150.0f)), rightArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_arm"]->transform.set(glm::vec4(-0.8f, -0.5f, -0.2f, glm::radians(60.0f)), leftArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_forearm"]->transform.set(glm::vec4(-0.1f, -0.3f, -1.0f, glm::radians(60.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_thigh"]->transform.set(glm::vec4(0.0f, 0.0f, -1.0f, glm::radians(12.0f)), rightThighOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_thigh"]->transform.set(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(12.0f)), leftThighOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_knee"]->transform.set(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(12.0f)), rightKneeOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_knee"]->transform.set(glm::vec4(0.0f, 0.0f, -1.0f, glm::radians(12.0f)), leftKneeOffset, glm::vec3(0, 0, 0));
		stage = stages;
	}
	else if (*stage == 10)
	{
		//setRightArmTrans2(deltaTime);
		//setLeftArmTrans2(deltaTime);
		//setRightForeArmTrans2(deltaTime);
		//setLeftForeArmTrans2(deltaTime);
		//setRightHandTrans(deltaTime);
		//setLeftHandTrans(deltaTime);
		model.componetMap["right_arm"]->transform.set(glm::vec4(-0.9f, -0.05f, 0.45f, glm::radians(42.0f)), rightArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_arm"]->transform.set(glm::vec4(-0.9f, 0.25f, -0.36f, glm::radians(45.0f)), leftArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_forearm"]->transform.set(glm::vec4(-0.225f, 0.96f, -0.18f, glm::radians(112.0f)), rightForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_forearm"]->transform.set(glm::vec4(-0.17f, -1.0f, -0.07f, glm::radians(105.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_hand"]->transform.set(glm::vec4(-0.1f, -0.23f, -0.97f, glm::radians(42.0f)), rightHandOffset, glm::vec3(0, 0, 0));
		model.componetMap["left_hand"]->transform.set(glm::vec4(-0.14f, 0.24f, 0.96f, glm::radians(32.0f)), leftHandOffset, glm::vec3(0, 0, 0));
		stage++;
	}
	else if (*stage % 2 == 1)
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

	if (*stage > 10)
	{
		setLeftForeArmTrans(deltaTime);
		setRightHandTrans(deltaTime);
		setLeftHandTrans(deltaTime);
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
		static int direction = 1;

		Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(112.0f), glm::radians(80.0f), glm::vec3(-0.225f, 0.96f, -0.18f), glm::vec3(0.0f, 0.97f, 0.25f)), (angle + direction * speed * deltaTime * 42.0f * 0.0335f)), rightForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_forearm"]->transform = newTrans;

		if (angle < glm::radians(80.0f) && direction == -1)
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

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(105.0f), glm::radians(90.0f), glm::vec3(-0.17f, -1.0f, -0.07f), glm::vec3(0.14f, -0.92f, -0.37f)), (angle + direction * speed * deltaTime * 15.0f * 0.0335f)), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform = newTrans;

	if (angle < glm::radians(90.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(105.0f) && direction == 1)
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
		stage++;
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
		stage++;
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
	static int direction = -1;

	float angle = model.componetMap["right_hand"]->transform.rotate.w;

	Transform newTrans(glm::vec4(-0.1f, -0.23f, -0.97f, (angle + direction * speed * deltaTime * 42.0f * 0.0135f)), rightHandOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_hand"]->transform = newTrans;

	if (angle < glm::radians(0.0f) && direction == -1)
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
	static int direction = -1;

	float angle = model.componetMap["left_hand"]->transform.rotate.w;

	Transform newTrans(glm::vec4(-0.14f, 0.24f, 0.96f, (angle + direction * speed * deltaTime * 32.0f * 0.0335f)), leftHandOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_hand"]->transform = newTrans;

	if (angle < glm::radians(0.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(32.0f) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setRightArmTrans2(const float& deltaTime)
{
	float angle = model.componetMap["right_arm"]->transform.rotate.w;
	static float startAngle = model.componetMap["right_arm"]->transform.rotate.w;
	static glm::vec3 startAxis = glm::vec3(model.componetMap["right_arm"]->transform.rotate);
	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, startAngle, glm::radians(42.0f), startAxis, glm::vec3(-0.9f, -0.05f, 0.45f)), (angle + speed * deltaTime * (glm::radians(42.0f) - startAngle))), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform = newTrans;

}

void GangnamAnimation::setLeftArmTrans2(const float& deltaTime)
{
	float angle = model.componetMap["left_arm"]->transform.rotate.w;

	static float startAngle = model.componetMap["left_arm"]->transform.rotate.w;
	static glm::vec3 startAxis = glm::vec3(model.componetMap["left_arm"]->transform.rotate);
	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, startAngle, glm::radians(45.0f), startAxis, glm::vec3(-0.9f, 0.25f, -0.36f)), (angle + speed * deltaTime * (glm::radians(45.0f) - startAngle))), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_arm"]->transform = newTrans;

	if (angle < glm::radians(45.0f))
	{
		stage++;
	}
}

void GangnamAnimation::setRightForeArmTrans2(const float& deltaTime)
{
	static float startAngle = model.componetMap["right_forearm"]->transform.rotate.w;

	static glm::vec3 startAxis = glm::vec3(model.componetMap["right_forearm"]->transform.rotate);
	float angle = model.componetMap["right_forearm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, startAngle, glm::radians(112.0f), startAxis, glm::vec3(-0.225f, 0.96f, -0.18f)), (angle + speed * deltaTime * (glm::radians(112.0f) - startAngle))), rightForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_forearm"]->transform = newTrans;
}

void GangnamAnimation::setLeftForeArmTrans2(const float& deltaTime)
{
	static float startAngle = model.componetMap["left_forearm"]->transform.rotate.w;

	static glm::vec3 startAxis = glm::vec3(model.componetMap["left_forearm"]->transform.rotate);
	float angle = model.componetMap["left_forearm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, startAngle, glm::radians(105.0f), startAxis, glm::vec3(-0.17f, -1.0f, -0.07f)), (angle + speed * deltaTime * (glm::radians(105.0f) - startAngle))), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform = newTrans;
}

glm::vec3 GangnamAnimation::rotateAxisWithRange(float angle, float angle_start, float angle_end, glm::vec3 axis_from, glm::vec3 axis_to)
{
	return glm::vec3(axis_from.x + (axis_to.x - axis_from.x) * (angle - angle_start) / (angle_end - angle_start),
		axis_from.y + (axis_to.y - axis_from.y) * (angle - angle_start) / (angle_end - angle_start),
		axis_from.z + (axis_to.z - axis_from.z) * (angle - angle_start) / (angle_end - angle_start));
}
