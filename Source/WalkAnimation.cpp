#include "WalkAnimation.h"

void WalkAnimation::Update(float deltaTime)
{
	float angle;
	bool done = true;
	switch (stage)
	{
	case 0:
		angle = model.componetMap["right_arm"]->transform.rotate.w;
		if (angle > glm::radians(-45.0f))
		{
			Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime)), glm::vec3(0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
			model.componetMap["right_arm"]->transform = newTrans;
			done = false;
		}
		angle = model.componetMap["left_arm"]->transform.rotate.w;
		if (angle < glm::radians(45.0f))
		{
			Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime)), glm::vec3(-0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
			model.componetMap["left_arm"]->transform = newTrans;
			done = false;
		}
		angle = model.componetMap["right_thigh"]->transform.rotate.w;
		if (angle < glm::radians(45.0f))
		{
			Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime)), glm::vec3(0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
			model.componetMap["right_thigh"]->transform = newTrans;
			done = false;
		}
		angle = model.componetMap["left_thigh"]->transform.rotate.w;
		if (angle > glm::radians(-45.0f))
		{
			Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime)), glm::vec3(-0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
			model.componetMap["left_thigh"]->transform = newTrans;
			done = false;
		}
		if (done)
			stage = 1;
		break;
	case 1:
		angle = model.componetMap["right_arm"]->transform.rotate.w;
		if (angle < glm::radians(45.0f))
		{
			Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime)), glm::vec3(0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
			model.componetMap["right_arm"]->transform = newTrans;
			done = false;
		}
		angle = model.componetMap["left_arm"]->transform.rotate.w;
		if (angle > glm::radians(-45.0f))
		{
			Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime)), glm::vec3(-0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
			model.componetMap["left_arm"]->transform = newTrans;
			done = false;
		}
		angle = model.componetMap["right_thigh"]->transform.rotate.w;
		if (angle > glm::radians(-45.0f))
		{
			Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime)), glm::vec3(0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
			model.componetMap["right_thigh"]->transform = newTrans;
			done = false;
		}
		angle = model.componetMap["left_thigh"]->transform.rotate.w;
		if (angle < glm::radians(45.0f))
		{
			Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime)), glm::vec3(-0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
			model.componetMap["left_thigh"]->transform = newTrans;
			done = false;
		}
		if (done)
			stage = 0;
		break;
	}
}
