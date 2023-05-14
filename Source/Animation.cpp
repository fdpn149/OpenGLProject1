#include "Animation.h"

Animation::Animation(Model& model, float speed)
	:model(model), stage(0), speed(speed)
{
	rightArmOffset = glm::vec3(0.5631f, -3.63f, 0.2089f);
	leftArmOffset = glm::vec3(-0.5631f, -3.63f, 0.2089f);

	rightThighOffset = glm::vec3(0.2835f, -2.176f, -0.00805f);
	leftThighOffset = glm::vec3(-0.2835f, -2.176f, -0.00805f);

	rightForeArmOffset = glm::vec3(0.8627f, -3.163f, 0.2554f);
	leftForeArmOffset = glm::vec3(-0.8627f, -3.163f, 0.2554f);

	rightKneeOffset = glm::vec3(0.3f, -1.48f, 0.0f);
	leftKneeOffset = glm::vec3(-0.3f, -1.48f, 0.0f);
}
