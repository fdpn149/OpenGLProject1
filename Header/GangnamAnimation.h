#pragma once
#include "Animation.h"

class GangnamAnimation : public Animation
{
	int* stage;
public:
	GangnamAnimation(Model& model, float speed);
	~GangnamAnimation();
	void update(const float& deltaTime);
private:
	int stages[18] = { 1,2,3,5,4,7,6,8,10,11,12,13,15,14,17,16,18,0 };
	glm::vec3 rotateAxisWithRange(float angle, float offset, float range, glm::vec3 from, glm::vec3 to);
	void action1Init();
	void action2Init();
	void setBodyTrans(const float deltaTime);
	void setRightArmTrans(const float& deltaTime);
	void setRightForeArmTrans(const float& deltaTime);
	void setLeftForeArmTrans(const float& deltaTime);
	void setRightThighTrans(float deltaTime);
	void setLeftThighTrans(float deltaTime);
	void setRightKneeTrans(float deltaTime);
	void setLeftKneeTrans(float deltaTime);
	void setRightHandTrans(float deltaTime);
	void setLeftHandTrans(float deltaTime);
};

