#pragma once
#include "Animation.h"

#include <glm/glm.hpp>

class WalkAnimation : public Animation
{
public: 
	WalkAnimation(Model& model, float speed)
		:Animation(model, speed)
	{
	}

	virtual void Update(float deltaTime) override;

private:
	void rotateComponetByAngle(std::string componet, glm::vec3 offset, float radians);

	void setRightArmTrans(float deltaTime);
	void setLeftArmTrans(float deltaTime);
	void setRightThighTrans(float deltaTime);
	void setLeftThighTrans(float deltaTime);
};

