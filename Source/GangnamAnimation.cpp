#include "GangnamAnimation.h"
#include <GLFW/glfw3.h>

GangnamAnimation::GangnamAnimation(Model& model, float speed)
	: Animation(model, speed)
{
	stage = &stages[0];

	action1Init();
}

GangnamAnimation::~GangnamAnimation()
{
	model.componetMap["left_arm"]->transform.set(glm::vec4(-0.5631f, -3.63f, 0.2089f, glm::radians(0.0f)), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform.set(glm::vec4(0.5631f, -3.63f, 0.2089f, glm::radians(0.0f)), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform.set(glm::vec4(-0.8627f, -3.163f, 0.2554f, glm::radians(0.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_forearm"]->transform.set(glm::vec4(0.8627f, -3.163f, 0.2554f, glm::radians(0.0f)), rightForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_thigh"]->transform.set(glm::vec4(-0.2835f, -2.24f, -0.00805f, glm::radians(0.0f)), leftThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_thigh"]->transform.set(glm::vec4(0.8627f, -3.163f, 0.2554f, glm::radians(0.0f)), rightThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_knee"]->transform.set(glm::vec4(-0.33f, -1.444f, 0.0f, glm::radians(0.0f)), leftKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_knee"]->transform.set(glm::vec4(0.33f, -1.444f, 0.0f, glm::radians(0.0f)), rightKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_hand"]->transform.set(glm::vec4(-1.26f, -2.574f, -0.1968f, glm::radians(0.0f)), leftHandOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_hand"]->transform.set(glm::vec4(1.26f, -2.574f, -0.1968f, glm::radians(0.0f)), rightHandOffset, glm::vec3(0, 0, 0));
}

void GangnamAnimation::action1Init()
{
	model.componetMap["left_arm"]->transform.set(glm::vec4(-0.8f, -0.5f, -0.2f, glm::radians(60.0f)), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform.set(glm::vec4(-1.0f, 0.2f, -0.05f, glm::radians(150.0f)), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform.set(glm::vec4(-0.1f, -0.3f, -1.0f, glm::radians(60.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_thigh"]->transform.set(glm::vec4(0.0f, 0.0f, -1.0f, glm::radians(12.0f)), rightThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_thigh"]->transform.set(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(12.0f)), leftThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_knee"]->transform.set(glm::vec4(0.0f, 0.0f, 1.0f, glm::radians(12.0f)), rightKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_knee"]->transform.set(glm::vec4(0.0f, 0.0f, -1.0f, glm::radians(12.0f)), leftKneeOffset, glm::vec3(0, 0, 0));
}

void GangnamAnimation::action2Init()
{
	model.componetMap["left_arm"]->transform.set(glm::vec4(-0.9f, 0.25f, -0.36f, glm::radians(45.0f)), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform.set(glm::vec4(-0.9f, -0.05f, 0.45f, glm::radians(42.0f)), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform.set(glm::vec4(0.06f, -0.5f, -0.8f, glm::radians(75.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_forearm"]->transform.set(glm::vec4(-0.22f, 0.96f, -0.18f, glm::radians(112.0f)), rightForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_hand"]->transform.set(glm::vec4(0.12f, -0.8f, 0.6f, glm::radians(112.0f)), leftHandOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_hand"]->transform.set(glm::vec4(-0.1f, -0.25f, -0.96f, glm::radians(42.0f)), rightHandOffset, glm::vec3(0, 0, 0));
}

void GangnamAnimation::update(const float& deltaTime)
{
	//printf("%d\n", *stage);
	setBodyTrans(deltaTime);
	if (*stage == 0)
	{
		action1Init();
		stage = stages;
	}
	else if (*stage == 10)
	{
		action2Init();
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

		float start_angle = 112.0f;
		float end_angle = 111.0f;
		glm::vec3 start_axis(-0.22f, 0.96f, -0.18f);
		glm::vec3 end_axis(0.0f, 1.0f, -0.08f);

		Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(start_angle), glm::radians(end_angle), start_axis, end_axis), (angle + direction * speed * deltaTime * (start_angle - end_angle) * 0.0335f)), rightForeArmOffset, glm::vec3(0, 0, 0));
		model.componetMap["right_forearm"]->transform = newTrans;

		if (angle < glm::radians(end_angle) && direction == -1)
		{
			direction = 1;
		}
		else if (angle > glm::radians(start_angle) && direction == 1)
		{
			direction = -1;
		}
	}
}

void GangnamAnimation::setLeftForeArmTrans(const float& deltaTime)
{
	float angle = model.componetMap["left_forearm"]->transform.rotate.w;

	static int direction = -1;

	float start_angle = 75.0f;
	float end_angle = 78.0f;
	glm::vec3 start_axis(0.06f, -0.5f, -0.8f);
	glm::vec3 end_axis(0.3f, -0.3f, -0.9f);

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(start_angle), glm::radians(end_angle), start_axis, end_axis), (angle + direction * speed * deltaTime * (end_angle - start_angle) * 0.0335f)), leftForeArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_forearm"]->transform = newTrans;

	if (angle < glm::radians(start_angle) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(end_angle) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setRightThighTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["right_thigh"]->transform.rotate.w;

	float start_angle = 12.0f;
	float end_angle = 50.0f;
	glm::vec3 start_axis(0.0f, 0.0f, -1.0f);
	glm::vec3 end_axis(-0.85f, 0.05f, -0.5f);

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(start_angle), glm::radians(end_angle), start_axis, end_axis), (angle + direction * speed * deltaTime * (end_angle - start_angle) * 0.0335f)), rightThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_thigh"]->transform = newTrans;

	if (angle < glm::radians(start_angle) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(end_angle) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setLeftThighTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_thigh"]->transform.rotate.w;

	float start_angle = 12.0f;
	float end_angle = 50.0f;
	glm::vec3 start_axis(0.0f, 0.0f, 1.0f);
	glm::vec3 end_axis(-0.85f, 0.05f, 0.5f);

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(start_angle), glm::radians(end_angle), start_axis, end_axis), (angle + direction * speed * deltaTime * (end_angle - start_angle) * 0.0335f)), leftThighOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_thigh"]->transform = newTrans;

	if (angle < glm::radians(start_angle) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(end_angle) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setRightKneeTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["right_knee"]->transform.rotate.w;

	float start_angle = 12.0f;
	float end_angle = 50.0f;
	glm::vec3 start_axis(0.0f, 0.0f, 1.0f);
	glm::vec3 end_axis(0.85f, -0.05f, 0.5f);

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(start_angle), glm::radians(end_angle), start_axis, end_axis), (angle + direction * speed * deltaTime * (end_angle - start_angle) * 0.0335f)), rightKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_knee"]->transform = newTrans;

	if (angle < glm::radians(start_angle) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(end_angle) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setLeftKneeTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_knee"]->transform.rotate.w;

	float start_angle = 12.0f;
	float end_angle = 50.0f;
	glm::vec3 start_axis(0.0f, 0.0f, -1.0f);
	glm::vec3 end_axis(0.85f, -0.05f, -0.5f);

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(start_angle), glm::radians(end_angle), start_axis, end_axis), (angle + direction * speed * deltaTime * (end_angle - start_angle) * 0.0335f)), leftKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_knee"]->transform = newTrans;

	if (angle < glm::radians(start_angle) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(end_angle) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setRightHandTrans(float deltaTime)
{
	float angle = model.componetMap["right_hand"]->transform.rotate.w;

	static int direction = -1;

	float start_angle = 42.0f;
	float end_angle = 14.0f;
	glm::vec3 start_axis(-0.1f, -0.25f, -0.96f);
	glm::vec3 end_axis(0.0f, -0.2f, -1.0f);

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(start_angle), glm::radians(end_angle), start_axis, end_axis), (angle + direction * speed * deltaTime * (start_angle - end_angle) * 0.0335f)), rightHandOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_hand"]->transform = newTrans;

	if (angle < glm::radians(end_angle) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(start_angle) && direction == 1)
	{
		direction = -1;
	}
}

void GangnamAnimation::setLeftHandTrans(float deltaTime)
{
	float angle = model.componetMap["left_hand"]->transform.rotate.w;

	static int direction = -1;

	float start_angle = 112.0f;
	float end_angle = 95.0f;
	glm::vec3 start_axis(0.12f, -0.8f, 0.6f);
	glm::vec3 end_axis(0.42f, -0.8f, 0.42f);

	Transform newTrans(glm::vec4(rotateAxisWithRange(angle, glm::radians(start_angle), glm::radians(end_angle), start_axis, end_axis), (angle + direction * speed * deltaTime * (start_angle - end_angle) * 0.0335f)), leftHandOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_hand"]->transform = newTrans;

	if (angle < glm::radians(end_angle) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(start_angle) && direction == 1)
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
