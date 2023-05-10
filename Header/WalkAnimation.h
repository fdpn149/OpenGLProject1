#pragma once
#include "Animation.h"

class WalkAnimation : public Animation
{
public: 
	WalkAnimation(Model& model, float speed)
		:Animation(model, speed)
	{}

	virtual void Update(float deltaTime) override;

};

