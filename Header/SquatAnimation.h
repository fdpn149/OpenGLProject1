#pragma once
#include "Animation.h"
class SquatAnimation : public Animation
{
public:
	SquatAnimation(Model& model, float speed) : Animation(model, speed){}
	virtual void update(const float& deltaTime) override;

private:
	void setBodyTrans(float deltaTime);
	void setWaistBaseTrans(float deltaTime);
	void setRightKneeTrans(float deltaTime);
	void setLeftKneeTrans(float deltaTime);
	void setRightFootTrans(float deltaTime);
	void setLeftFootTrans(float deltaTime);

	void setRightArmTrans(float deltaTime);
	void setLeftArmTrans(float deltaTime);
	void setRightForeArmTrans(float deltaTime);
	void setLeftForeArmTrans(float deltaTime);
};

