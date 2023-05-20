#include "PushUpAnimation.h"

PushUpAnimation::PushUpAnimation(Model& model, float speed)
	:Animation(model, speed), foreArmDir(1)
{
	// init right arm
	Transform trans(glm::vec4(1.0f, 0.0f, -0.4f, glm::radians(-15.0f)), rightArmOffset, glm::vec3(0.0f, 0.0f, 0.0f));
	model.componetMap["right_arm"]->transform = trans;

	// init left arm
	trans = Transform(glm::vec4(1.0f, 0.0f, 0.4f, glm::radians(-15.0f)), leftArmOffset, glm::vec3(0.0f, 0.0f, 0.0f));
	model.componetMap["left_arm"]->transform = trans;

	// init right forearm
	trans = Transform(glm::vec4(-0.3f, 0.6f, -0.3f, glm::radians(70.0f)), rightForeArmOffset, glm::vec3(0.0f, 0.0f, 0.0f));
	model.componetMap["right_forearm"]->transform = trans;

	// init left forearm
	trans = Transform(glm::vec4(-0.3f, -0.6f, 0.3f, glm::radians(70.0f)), leftForeArmOffset, glm::vec3(0.0f, 0.0f, 0.0f));
	model.componetMap["left_forearm"]->transform = trans;

	// init right hands
	trans = Transform(glm::vec4(0.7f, 0.5f, 1.0f, glm::radians(-90.0f)), rightHandOffset, glm::vec3(0.0f, 0.0f, 0.0f));
	model.componetMap["right_hand"]->transform = trans;

	// init left hands
	trans = Transform(glm::vec4(-0.7f, 0.5f, 1.0f, glm::radians(90.0f)), leftHandOffset, glm::vec3(0.0f, 0.0f, 0.0f));
	model.componetMap["left_hand"]->transform = trans;


	// init model transform
	modelRotation = glm::radians(77.5f);
	modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, modelRotation, glm::vec3(1.0f, 0.0f, 0.0f));
}

PushUpAnimation::~PushUpAnimation()
{
	model.componetMap["right_arm"]->transform = Transform();
	model.componetMap["left_arm"]->transform = Transform();
	model.componetMap["right_forearm"]->transform = Transform();
	model.componetMap["left_forearm"]->transform = Transform();
	model.componetMap["right_hand"]->transform = Transform();
	model.componetMap["left_hand"]->transform = Transform();
}

void PushUpAnimation::update(const float& deltaTime)
{
	setModelMat(deltaTime);
	setArm(deltaTime);
	setLeftForeArm(deltaTime);
	setRightForeArm(deltaTime);

	
	model.updateTransforms(modelMat);
}

void PushUpAnimation::setArm(float deltaTime)
{
	float angle = model.componetMap["right_arm"]->transform.rotate.w;

	float newAngle = angle - foreArmDir * speed * deltaTime * (65.0f /56.0f);

	Transform newTrans(glm::vec4(1.0f, 0.0f, -0.4, newAngle), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform = newTrans;

	newTrans = Transform(glm::vec4(1.0f, 0.0f, 0.4, newAngle), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_arm"]->transform = newTrans;
}

void PushUpAnimation::setRightForeArm(float deltaTime)
{
	float angle = model.componetMap["right_forearm"]->transform.rotate.w;
	float rotationX = model.componetMap["right_forearm"]->transform.rotate.x * angle;

	rotationX += foreArmDir * speed * deltaTime;
	model.componetMap["right_forearm"]->transform.rotate.x = rotationX / angle;

	if (rotationX < glm::radians(-21.0f) && foreArmDir == -1)
	{
		foreArmDir = 1;
	}
	else if (rotationX > glm::radians(35.0f) && foreArmDir == 1)
	{
		foreArmDir = -1;
	}
}

void PushUpAnimation::setLeftForeArm(float deltaTime)
{
	float angle = model.componetMap["left_forearm"]->transform.rotate.w;
	float rotationX = model.componetMap["left_forearm"]->transform.rotate.x * angle;

	rotationX += foreArmDir * speed * deltaTime;
	model.componetMap["left_forearm"]->transform.rotate.x = rotationX / angle;

	if (rotationX < glm::radians(-21.0f) && foreArmDir == -1)
	{
		foreArmDir = 1;
	}
	else if (rotationX > glm::radians(35.0f) && foreArmDir == 1)
	{
		foreArmDir = -1;
	}
}

void PushUpAnimation::setModelMat(float deltaTime)
{
	modelRotation -= foreArmDir * speed * deltaTime * (10.0f / 56.0f);

	modelMat = glm::rotate(glm::mat4(1.0f), modelRotation, glm::vec3(1.0f, 0.0f, 0.0f));
}
