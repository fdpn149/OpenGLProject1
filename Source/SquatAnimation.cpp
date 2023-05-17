#include "SquatAnimation.h"

void SquatAnimation::Update(float deltaTime)
{
	setBodyTrans(deltaTime);
	setWaistBaseTrans(deltaTime);
	setRightKneeTrans(deltaTime);
	setLeftKneeTrans(deltaTime);
	setRightFootTrans(deltaTime);
	setLeftFootTrans(deltaTime);

	setRightArmTrans(deltaTime);
	setLeftArmTrans(deltaTime);
	setRightForeArmTrans(deltaTime);
	setLeftForeArmTrans(deltaTime);

	model.updateTransforms(glm::mat4(1.0f));
}

void SquatAnimation::setBodyTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["body_base"]->transform.rotate.w;
	glm::vec3 pos = model.componetMap["body_base"]->transform.translate;
	
	const float WAIST = 2.704244f;
	const float KNEE = 1.35f;
	const float FOOT = 0.45f;
	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + direction * speed * 0.25f * deltaTime)), bodyOffset, (glm::vec3(0, (-WAIST * (1.0f - glm::cos(3 * angle)) + KNEE * (glm::cos(angle) - glm::cos(3 * angle)) + FOOT * (1-glm::cos(angle))),(-WAIST * (glm::sin(3 * angle)) + KNEE * (glm::sin(angle) + glm::sin(angle * 3)) - FOOT * glm::sin(FOOT)))));
	model.componetMap["body_base"]->transform = newTrans;

	if (angle < glm::radians(0.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(30.0f) && direction == 1)
	{
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

void SquatAnimation::setRightArmTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["right_arm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + direction * speed * 0.75f * deltaTime)), rightArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_arm"]->transform = newTrans;

	if (angle < glm::radians(-90.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(0.0f) && direction == 1)
	{
		direction = -1;
	}
}

void SquatAnimation::setLeftArmTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["left_arm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + direction * speed * 0.75f * deltaTime)), rightArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_arm"]->transform = newTrans;

	if (angle < glm::radians(-90.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(0.0f) && direction == 1)
	{
		direction = -1;
	}
}

void SquatAnimation::setRightForeArmTrans(float deltaTime)
{
	static int direction = -1;

	float angle = model.componetMap["right_forearm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.0f, -0.3f, -0.6f, (angle + direction * speed * 0.33f * deltaTime)), rightForeArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_forearm"]->transform = newTrans;

	if (angle < glm::radians(-40.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(0.0f) && direction == 1)
	{
		direction = -1;
	}
}

void SquatAnimation::setLeftForeArmTrans(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_forearm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.0f, -0.3f, -0.6f, (angle + direction * speed * 0.33f * deltaTime)), leftForeArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_forearm"]->transform = newTrans;

	if (angle < glm::radians(0.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(40.0f) && direction == 1)
	{
		direction = -1;
	}
}
