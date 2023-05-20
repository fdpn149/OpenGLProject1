#pragma once
#include "Animation.h"
class SitupAnimation : public Animation
{
public:
	SitupAnimation(Model& model, float speed);

	~SitupAnimation();

	void update(const float& deltaTime);
private:
	void setLieBodyTrans(const float& deltaTime, bool& changeStage);
	void setLieWaistBaseTrans(const float& deltaTime, bool& changeStage);
	void setLieRightKneeTrans(const float& deltaTime, bool& changeStage);
	void setLieLeftKneeTrans(const float& deltaTime, bool& changeStage);
	void setLieRightFootTrans(const float& deltaTime, bool& changeStage);
	void setLieLeftFootTrans(const float& deltaTime, bool& changeStage);
	void setLieRightArmTrans(const float& deltaTime, bool& changeStage);
	void setLieLeftArmTrans(const float& deltaTime, bool& changeStage);
	void setLieRightForeArmTrans(const float& deltaTime, bool& changeStage);
	void setLieLeftForeArmTrans(const float& deltaTime, bool& changeStage);

	void setBodyTrans(const float& deltaTime);
	void setWaistBaseTrans(const float& deltaTime);

private:
	int stage;

	int bodyDir;
};

