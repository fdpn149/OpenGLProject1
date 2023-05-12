#pragma once

#include "Animation.h"

class JackpotAnimation : public Animation
{
public:
	JackpotAnimation(Model& model, float speed)
		:Animation(model, speed)
	{}

	virtual void Update(float deltaTime) override;

private:
	void setRightArmTrans(float deltaTime);
	void setLeftArmTrans(float deltaTime);
	void setRightForeArmTrans(float deltaTime);
	void setLeftForeArmTrans(float deltaTime);
	void setRightThighTrans(float deltaTime);
	void setLeftThighTrans(float deltaTime);
};