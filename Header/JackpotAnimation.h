#pragma once

#include "Animation.h"

class JackpotAnimation : public Animation
{
public:
	JackpotAnimation(Model& model, float speed);
	~JackpotAnimation();


	virtual void update(const float& deltaTime) override;

private:
	glm::mat4 getModel(float deltaTime);

	void setRightArmTrans(float deltaTime);
	void setLeftArmTrans(float deltaTime);
	void setRightForeArmTrans(float deltaTime);
	void setLeftForeArmTrans(float deltaTime);
	void setRightThighTrans(float deltaTime);
	void setLeftThighTrans(float deltaTime);

private:
	float jumpHeight;
	int rightForeArmDir;
};