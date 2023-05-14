#include "SquatAnimation.h"

void SquatAnimation::Update(float deltaTime)
{
	setBodyTrans(deltaTime);
	setWaistBaseTrans(deltaTime);
	setRightKneeTrans(deltaTime);
	setLeftKneeTrans(deltaTime);
	setRightFootTrans(deltaTime);
	setLeftFootTrans(deltaTime);

	model.updateTransforms(glm::mat4(1.0f));
}

void SquatAnimation::setBodyTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["body_base"]->transform.rotate.w;
	glm::vec3 pos = model.componetMap["body_base"]->transform.translate;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + direction * speed * 0.25 * deltaTime)), bodyOffset, (glm::vec3(0, (pos.y - 1.4482f * deltaTime * speed * direction *0.475f), (pos.z - 0.7516f * deltaTime * speed * direction *0.477f))));

	model.componetMap["body_base"]->transform = newTrans;

	if (angle < glm::radians(0.0f) && direction == -1)
	{
		printf("%f, %f, %f\n", newTrans.translate.x, newTrans.translate.y, newTrans.translate.z);
		direction = 1;
	}
	else if (angle > glm::radians(30.0f) && direction == 1)
	{
		printf("%f, %f, %f\n", newTrans.translate.x,newTrans.translate.y, newTrans.translate.z);
		direction = -1;
	}
}

void SquatAnimation::setWaistBaseTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["waist_base"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + direction * speed * deltaTime)), waistBaseOffset, glm::vec3(0, 0, 0));

	model.componetMap["waist_base"]->transform = newTrans;

	if (angle < glm::radians(-120.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(0.0f) && direction == 1)
	{
		direction = -1;
	}
}

void SquatAnimation::setRightKneeTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["right_knee"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + direction * speed * deltaTime)), rightKneeOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_knee"]->transform = newTrans;

	if (angle < glm::radians(0.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(120.0f) && direction == 1)
	{
		direction = -1;
	}
}

void SquatAnimation::setLeftKneeTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_knee"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + direction * speed * deltaTime)), leftKneeOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_knee"]->transform = newTrans;

	if (angle < glm::radians(0.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(120.0f) && direction == 1)
	{
		direction = -1;
	}
}

void SquatAnimation::setRightFootTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["right_foot"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + direction * speed * 0.25f * deltaTime)), rightFootOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_foot"]->transform = newTrans;

	if (angle < glm::radians(-30.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(0.0f) && direction == 1)
	{
		direction = -1;
	}
}

void SquatAnimation::setLeftFootTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["left_foot"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + direction * speed * 0.25f * deltaTime)), leftFootOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_foot"]->transform = newTrans;

	if (angle < glm::radians(-30.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(0.0f) && direction == 1)
	{
		direction = -1;
	}
}