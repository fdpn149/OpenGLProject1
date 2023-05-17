#include "Animation.h"

Animation::Animation(Model& model, float speed)
	:model(model), speed(speed)
{
	bodyOffset = glm::vec3(0.0f, -2.56f, 0.0f);

	waistBaseOffset = glm::vec3(0.0f, -2.7f, 0.0f);

	rightArmOffset = glm::vec3(0.5631f, -3.63f, 0.2089f);
	leftArmOffset = glm::vec3(-0.5631f, -3.63f, 0.2089f);

	rightThighOffset = glm::vec3(0.2835f, -2.24f, -0.00805f);
	leftThighOffset = glm::vec3(-0.2835f, -2.24f, -0.00805f);

	rightForeArmOffset = glm::vec3(0.8627f, -3.163f, 0.2554f);
	leftForeArmOffset = glm::vec3(-0.8627f, -3.163f, 0.2554f);

	rightKneeOffset = glm::vec3(0.33f, -1.444f, 0.0f);
	leftKneeOffset = glm::vec3(-0.33f, -1.444f, 0.0f);

	rightFootOffset = glm::vec3(0.45f, -0.27f, 0.111f);
	leftFootOffset = glm::vec3(-0.45f, -0.27f, 0.111f);
}
