#include "PushUpAnimation.h"

PushUpAnimation::PushUpAnimation(Model& model, float speed)
	:Animation(model, speed)
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
	static int direction = -1;

	float angle = model.componetMap["right_arm"]->transform.rotate.w;

	Transform newTrans(glm::vec4(1.0f, 0.0f, -0.4, (angle + direction * speed * deltaTime * 1.1607f)), rightArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["right_arm"]->transform = newTrans;

	newTrans = Transform(glm::vec4(1.0f, 0.0f, 0.4, (angle + direction * speed * deltaTime * 1.1607f)), leftArmOffset, glm::vec3(0, 0, 0));
	model.componetMap["left_arm"]->transform = newTrans;

	if (angle < glm::radians(-80.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (angle > glm::radians(-15.0f) && direction == 1)
	{
		direction = -1;
	}
}

void PushUpAnimation::setRightForeArm(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["right_forearm"]->transform.rotate.w;
	float rotationX = model.componetMap["right_forearm"]->transform.rotate.x * angle;

	rotationX += direction * speed * deltaTime;
	model.componetMap["right_forearm"]->transform.rotate.x = rotationX / angle;

	if (rotationX < glm::radians(-21.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (rotationX > glm::radians(35.0f) && direction == 1)
	{
		direction = -1;
	}
}

void PushUpAnimation::setLeftForeArm(float deltaTime)
{
	static int direction = 1;

	float angle = model.componetMap["left_forearm"]->transform.rotate.w;
	float rotationX = model.componetMap["left_forearm"]->transform.rotate.x * angle;

	rotationX += direction * speed * deltaTime;
	model.componetMap["left_forearm"]->transform.rotate.x = rotationX / angle;

	if (rotationX < glm::radians(-21.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (rotationX > glm::radians(35.0f) && direction == 1)
	{
		direction = -1;
	}
}

void PushUpAnimation::setModelMat(float deltaTime)
{
	static int direction = -1;

	modelRotation += direction * speed * deltaTime * 0.13392f;

	modelMat = glm::rotate(glm::mat4(1.0f), modelRotation, glm::vec3(1.0f, 0.0f, 0.0f));

	if (modelRotation < glm::radians(70.0f) && direction == -1)
	{
		direction = 1;
	}
	else if (modelRotation > glm::radians(77.5f) && direction == 1)
	{
		direction = -1;
	}
}
