#include "../Header/Transform.h"
#include "../Header/Mesh.h"
#include <glm/gtc/matrix_transform.hpp>

std::map<std::string, Transform> Transform::trans;
int Transform::stage = 0;
float Transform::speed = 2.0f;

Transform::Transform()
{
	scale = glm::vec3(1.0f);
	rotate = glm::vec4(0, 0, 1.0, glm::radians(0.0f));
	translate = glm::vec3(0);
}

Transform::Transform(glm::vec3 scale, glm::vec4 rotate, glm::vec3 translate)
{
	this->scale = scale;
	this->rotate = rotate;
	this->translate = translate;
}

void Transform::HierarchyTrans(glm::mat4& modelMat, Node* node)
{
	if (node != nullptr)
	{
		Node* tempNode = node->parent;
		HierarchyTrans(modelMat, tempNode);
		if (Transform::trans.find(node->name) != Transform::trans.end())
		{
			modelMat = glm::translate(modelMat, -Transform::trans[node->name].translate);
			modelMat = glm::rotate(modelMat, Transform::trans[node->name].rotate.w, glm::vec3(Transform::trans[node->name].rotate));
			modelMat = glm::scale(modelMat, Transform::trans[node->name].scale);
			modelMat = glm::translate(modelMat, Transform::trans[node->name].translate);
		}
	}
}

void Transform::move(std::string part, glm::vec3 scale, glm::vec4 rotate, glm::vec3 translate)
{
	if (trans.find(part) != trans.end())
		trans[part] = Transform(scale, rotate, translate);
	else
		printf("Cannot move %s!\n", part.c_str());
}

void Transform::Idle()
{
	stage = 0;
	for (std::map<std::string, Transform>::iterator i = trans.begin(); i != trans.end(); i++)
	{
		i->second.scale = glm::vec3(1.0f);
		i->second.rotate = glm::vec4(0, 0, 1.0f, glm::radians(0.0f));
		i->second.translate = glm::vec3(0);
	}
}

void Transform::Walk(float deltaTime)
{
	float angle;
	bool done = true;
	switch (stage)
	{
	case 0:
		angle = trans["right_arm"].rotate.w;
		if (angle > glm::radians(-45.0f))
		{
			move("right_arm", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0, 0.0, 0.0f, (angle - speed * deltaTime)), glm::vec3(0.5631f, -3.63f, 0.2089f));
			done = false;
		}
		angle = trans["left_arm"].rotate.w;
		if (angle < glm::radians(45.0f))
		{
			move("left_arm", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0, 0.0, 0.0f, (angle + speed * deltaTime)), glm::vec3(-0.5631f, -3.63f, 0.2089f));
			done = false;
		}
		angle = trans["right_thigh"].rotate.w;
		if (angle < glm::radians(45.0f))
		{
			move("right_thigh", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0, 0.0, 0.0f, (angle + speed * deltaTime)), glm::vec3(0.2835f, -2.176f, -0.00805f));
			done = false;
		}
		angle = trans["left_thigh"].rotate.w;
		if (angle > glm::radians(-45.0f))
		{
			move("left_thigh", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0, 0.0, 0.0f, (angle - speed * deltaTime)), glm::vec3(-0.2835f, -2.176f, -0.00805f));
			done = false;
		}
		if (done)
			stage = 1;
		break;
	case 1:
		angle = trans["right_arm"].rotate.w;
		if (angle < glm::radians(45.0f))
		{
			move("right_arm", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0, 0.0, 0.0f, (angle + speed * deltaTime)), glm::vec3(0.5631f, -3.63f, 0.2089f));
			done = false;
		}
		angle = trans["left_arm"].rotate.w;
		if (angle > glm::radians(-45.0f))
		{
			move("left_arm", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0, 0.0, 0.0f, (angle - speed * deltaTime)), glm::vec3(-0.5631f, -3.63f, 0.2089f));
			done = false;
		}
		angle = trans["right_thigh"].rotate.w;
		if (angle > glm::radians(-45.0f))
		{
			move("right_thigh", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0, 0.0, 0.0f, (angle - speed * deltaTime)), glm::vec3(0.2835f, -2.176f, -0.00805f));
			done = false;
		}
		angle = trans["left_thigh"].rotate.w;
		if (angle < glm::radians(45.0f))
		{
			move("left_thigh", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0, 0.0, 0.0f, (angle + speed * deltaTime)), glm::vec3(-0.2835f, -2.176f, -0.00805f));
			done = false;
		}
		if (done)
			stage = 0;
		break;
	}
}
