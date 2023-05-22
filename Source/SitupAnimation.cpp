#include "SitupAnimation.h"

SitupAnimation::SitupAnimation(Model& model, float speed)
	: Animation(model, speed), stage(0), bodyDir(1)
{

}

SitupAnimation::~SitupAnimation()
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

void SitupAnimation::update(const float& deltaTime)
{
	if (stage == 0)
	{
		bool changeStage = true;
		setLieBodyTrans(deltaTime, changeStage);
		setLieWaistBaseTrans(deltaTime, changeStage);
		setLieRightKneeTrans(deltaTime, changeStage);
		setLieLeftKneeTrans(deltaTime, changeStage);
		setLieRightFootTrans(deltaTime, changeStage);
		setLieLeftFootTrans(deltaTime, changeStage);
		setLieRightArmTrans(deltaTime, changeStage);
		setLieLeftArmTrans(deltaTime, changeStage);
		setLieRightForeArmTrans(deltaTime, changeStage);
		setLieLeftForeArmTrans(deltaTime, changeStage);
		if (changeStage)
			stage = 1;
	}
	else if(stage == 1)
	{
		setBodyTrans(deltaTime);
		setWaistBaseTrans(deltaTime);
	}

	model.updateTransforms(glm::mat4(1.0f));
}

void SitupAnimation::setLieBodyTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["body_base"]->transform.rotate.w;

	glm::vec3 off = model.componetMap["body_base"]->transform.offset;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime * 85.0f / 180.0f)), glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
	model.componetMap["body_base"]->transform = newTrans;

	if (angle > glm::radians(-85.0f))
		changeStage = false;
}

void SitupAnimation::setLieWaistBaseTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["waist_base"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime * 60.0f / 180.0f)), waistBaseOffset, glm::vec3(0, 0, 0));
	model.componetMap["waist_base"]->transform = newTrans;

	if (angle > glm::radians(-60.0f))
		changeStage = false;
}

void SitupAnimation::setLieRightKneeTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["right_knee"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime * 95.0f / 180.0f)), rightKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_knee"]->transform = newTrans;

	if (angle < glm::radians(95.0f))
		changeStage = false;
}

void SitupAnimation::setLieLeftKneeTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["left_knee"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime * 95.0f / 180.0f)), leftKneeOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_knee"]->transform = newTrans;

	if (angle < glm::radians(95.0f))
		changeStage = false;
}

void SitupAnimation::setLieRightFootTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["right_foot"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime * 50.0f / 180.0f)), rightFootOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_foot"]->transform = newTrans;

	if (angle < glm::radians(50.0f))
		changeStage = false;
}

void SitupAnimation::setLieLeftFootTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["left_foot"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime * 50.0f / 180.0f)), leftFootOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_foot"]->transform = newTrans;

	if (angle < glm::radians(50.0f))
		changeStage = false;
}

void SitupAnimation::setLieRightArmTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["right_arm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(-0.85f, -0.3f,  0.35f, (angle + speed * deltaTime * 120.0f / 180.0f)), rightArmOffset, glm::vec3(0, 0, 0));
	
	model.componetMap["right_arm"]->transform = newTrans;

	if (angle < glm::radians(120.0f))
		changeStage = false;
}

void SitupAnimation::setLieLeftArmTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["left_arm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(-0.85f, 0.3f, -0.35f, (angle + speed * deltaTime * 120.0f / 180.0f)), leftArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_arm"]->transform = newTrans;

	if (angle < glm::radians(62.9f))
		changeStage = false;
}

void SitupAnimation::setLieRightForeArmTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["right_forearm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.05f, 0.25f, 1.0f, (angle + speed * deltaTime * 120.0f / 180.0f)), rightForeArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["right_forearm"]->transform = newTrans;

	if (angle < glm::radians(95.4f))
		changeStage = false;
}

void SitupAnimation::setLieLeftForeArmTrans(const float& deltaTime, bool& changeStage)
{
	float angle = model.componetMap["left_forearm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(0.05f, -0.25f, -1.0f, (angle + speed * deltaTime * 120.0f / 180.0f)), leftForeArmOffset, glm::vec3(0, 0, 0));

	model.componetMap["left_forearm"]->transform = newTrans;

	if (angle < glm::radians(97.7f))
		changeStage = false;
}

void SitupAnimation::setBodyTrans(const float& deltaTime)
{
	float angle = model.componetMap["body_base"]->transform.rotate.w;

	float newAngle = angle + bodyDir * speed * deltaTime * 75.0f / 180.0f;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), bodyOffset, bodyOffset - glm::vec3(0, -0.2243f, 2.552f));

	model.componetMap["body_base"]->transform = newTrans;

	if (angle < glm::radians(-85.0f) && bodyDir == -1)
	{
		bodyDir = 1;
	}
	else if (angle > glm::radians(-10.0f) && bodyDir == 1)
	{
		bodyDir = -1;
	}
}

void SitupAnimation::setWaistBaseTrans(const float& deltaTime)
{
	float angle = model.componetMap["waist_base"]->transform.rotate.w;

	float newAngle = angle - bodyDir * speed * deltaTime * 75.0f / 180.0f;

	Transform newTrans(glm::vec4(1.0f, 0.0f, 0.0f, newAngle), waistBaseOffset, glm::vec3(0, 0, 0));

	model.componetMap["waist_base"]->transform = newTrans;

	//if (angle > glm::radians(-60.0f) && waistDir == -1)
	//{
	//	waistDir = 1;
	//}
	//else if (angle < glm::radians(-135.0f) && waistDir == 1)
	//{
	//	waistDir = -1;
	//}
}

