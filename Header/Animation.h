#pragma once

#include "Model.h"

class Animation
{
public:
	Animation(Model& model, float speed)
		:model(model), stage(0), speed(speed)
	{}

	virtual void Update(float deltaTime) = 0;


protected:
	Model& model;

	int stage;

	float speed;
};

