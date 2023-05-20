#include "SquatAnimation.h"

SquatAnimation::SquatAnimation(Model& model, float speed)
	:Animation(model, speed),
	waistDir(-1)
{

}

SquatAnimation::~SquatAnimation()
{
	model.componetMap["body_base"]->transform = Transform();
	model.componetMap["waist_base"]->transform = Transform();
	model.componetMap["right_arm"]->transform = Transform();
	model.componetMap["left_arm"]->transform = Transform();
	model.componetMap["right_forearm"]->transform = Transform();
	model.componetMap["left_forearm"]->transform = Transform();
	model.componetMap["right_knee"]->transform = Transform();
	model.componetMap["left_knee"]->transform = Transform();
	model.componetMap["right_foot"]->transform = Transform();
	model.componetMap["left_foot"]->transform = Transform();
}

void SquatAnimation::update(const float& deltaTime)
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
	float angle = model.componetMap["body_base"]->transform.rotate.w;
	glm::vec3 pos = model.componetMap["body_base"]->transform.translate;
	
	const float WAIST = 2.704244f;
	const float KNEE = 1.35f;
	const float FOOT = 0.45f;
	
	float newAngle = angle - waistDir * speed * 0.25f * deltaTime;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), bodyOffset, (glm::vec3(0, (-WAIST * (1.0f - glm::cos(3 * angle)) + KNEE * (glm::cos(angle) - glm::cos(3 * angle)) + FOOT * (1-glm::cos(angle))), (-WAIST * (glm::sin(3 * angle)) + KNEE * (glm::sin(angle) + glm::sin(angle * 3)) - FOOT * glm::sin(FOOT)))));
	model.componetMap["body_base"]->transform = newTrans;
}

void SquatAnimation::setWaistBaseTrans(float deltaTime)
{
	float angle = model.componetMap["waist_base"]->transform.rotate.w;

	float newAngle = angle + waistDir * speed * deltaTime;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), waistBaseOffset, glm::vec3(0, 0, 0));

	model.componetMap["waist_base"]->transform = newTrans;

	if (angle < glm::radians(-120.0f) && waistDir == -1)
	{
		waistDir = 1;
	}
	else if (angle > glm::radians(0.0f) && waistDir == 1)
	{
		waistDir = -1;
	}
}

void SquatAnimation::setRightKneeTrans(float deltaTime)
{
	float angle = model.componetMap["right_knee"]->transform.rotate.w;

	float newAngle = angle - waistDir * speed * deltaTime;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), rightKneeOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_knee"]->transform = newTrans;
}

void SquatAnimation::setLeftKneeTrans(float deltaTime)
{
	float angle = model.componetMap["left_knee"]->transform.rotate.w;

	float newAngle = angle - waistDir * speed * deltaTime;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), leftKneeOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_knee"]->transform = newTrans;

}

void SquatAnimation::setRightFootTrans(float deltaTime)
{
	float angle = model.componetMap["right_foot"]->transform.rotate.w;

	float newAngle = angle + waistDir * speed * 0.25f * deltaTime;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), rightFootOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_foot"]->transform = newTrans;
}

void SquatAnimation::setLeftFootTrans(float deltaTime)
{
	float angle = model.componetMap["left_foot"]->transform.rotate.w;

	float newAngle = angle + waistDir * speed * 0.25f * deltaTime;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), leftFootOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_foot"]->transform = newTrans;
}

void SquatAnimation::setRightArmTrans(float deltaTime)
{
	float angle = model.componetMap["right_arm"]->transform.rotate.w;

	float newAngle = angle + waistDir * speed * 0.75f * deltaTime;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), rightArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_arm"]->transform = newTrans;
}

void SquatAnimation::setLeftArmTrans(float deltaTime)
{
	float angle = model.componetMap["left_arm"]->transform.rotate.w;

	float newAngle = angle + waistDir * speed * 0.75f * deltaTime;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), rightArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_arm"]->transform = newTrans;
}

void SquatAnimation::setRightForeArmTrans(float deltaTime)
{
	float angle = model.componetMap["right_forearm"]->transform.rotate.w;

	float newAngle = angle + waistDir * speed * 0.33f * deltaTime;

	Transform newTrans(glm::vec4(0.0f, -0.3f, -0.6f, newAngle), rightForeArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_forearm"]->transform = newTrans;
}

void SquatAnimation::setLeftForeArmTrans(float deltaTime)
{
	float angle = model.componetMap["left_forearm"]->transform.rotate.w;

	float newAngle = angle - waistDir * speed * 0.33f * deltaTime;

	Transform newTrans(glm::vec4(0.0f, -0.3f, -0.6f, newAngle), leftForeArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_forearm"]->transform = newTrans;
}
