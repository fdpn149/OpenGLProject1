#pragma once
#include "Animation.h"
#include "Model.h"

class PushUpAnimation : public Animation
{
public: 

	PushUpAnimation(Model& model, float speed);
	~PushUpAnimation();


	void update(const float& deltaTime) override;

private:
	void setArm(float deltaTime);
	void setRightForeArm(float deltaTime);
	void setLeftForeArm(float deltaTime);
	void setModelMat(float deltaTime);

private:
	float modelRotation;
	glm::mat4 modelMat;

	int foreArmDir;
};