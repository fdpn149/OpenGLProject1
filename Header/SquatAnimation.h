#pragma once
#include "Animation.h"
class SquatAnimation : public Animation
{
	int stage;
public:
	SquatAnimation(Model& model, float speed) : Animation(model, speed)
	{
		stage = 0;
	}
	virtual void Update(float deltaTime) override;

private:
	void setBodyTrans(float deltaTime);
	void setWaistBaseTrans(float deltaTime);
	void setRightKneeTrans(float deltaTime);
	void setLeftKneeTrans(float deltaTime);
	void setRightFootTrans(float deltaTime);
	void setLeftFootTrans(float deltaTime);
};

