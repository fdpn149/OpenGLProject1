#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"

#include <iostream>

//std::map<std::string, Transform> Transform::trans;
//int Transform::stage = 0;
//float Transform::speed = 2.0f;

Transform::Transform()
{
	rotate = glm::vec4(0, 0, 1.0, glm::radians(0.0f));
	offset = glm::vec3(0);
	translate = glm::vec3(0);
}

Transform::Transform(glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate)
{
	this->rotate = rotate;
	this->offset = offset;
	this->translate = translate;
}

void Transform::set(glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate)
{
	this->rotate = rotate;
	this->offset = offset;
	this->translate = translate;
}

//void Transform::HierarchyTrans(glm::mat4& modelMat, Node* node)
//{
//	if (node != nullptr)
//	{
//		Node* tempNode = node->parent;
//		HierarchyTrans(modelMat, tempNode);
//		if (Transform::trans.find(node->name) != Transform::trans.end())
//		{
//			modelMat = glm::translate(modelMat, Transform::trans[node->name].translate);
//			modelMat = glm::translate(modelMat, -Transform::trans[node->name].offset);
//			modelMat = glm::rotate(modelMat, Transform::trans[node->name].rotate.w, glm::vec3(Transform::trans[node->name].rotate));
//			modelMat = glm::translate(modelMat, Transform::trans[node->name].offset);
//		}
//	}
//}
//
//void Transform::move(std::string part, glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate)
//{
//	if (trans.find(part) != trans.end())
//		trans[part] = Transform(rotate, offset, translate);
//	else
//		printf("Cannot move %s!\n", part.c_str());
//}
//
//void Transform::Idle()
//{
//	stage = 0;
//	for (std::map<std::string, Transform>::iterator i = trans.begin(); i != trans.end(); i++)
//	{
//		i->second.rotate = glm::vec4(0, 0, 1.0f, glm::radians(0.0f));
//		i->second.offset = glm::vec3(0);
//		i->second.translate = glm::vec3(0);
//	}
//}
//
//void Transform::Walk(float deltaTime)
//{
//	float angle;
//	bool done = true;
//	switch (stage)
//	{
//	case 0:
//		angle = trans["right_arm"].rotate.w;
//		if (angle > glm::radians(-45.0f))
//		{
//			move("right_arm", glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime)), glm::vec3(0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_arm"].rotate.w;
//		if (angle < glm::radians(45.0f))
//		{
//			move("left_arm", glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime)), glm::vec3(-0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["right_thigh"].rotate.w;
//		if (angle < glm::radians(45.0f))
//		{
//			move("right_thigh", glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime)), glm::vec3(0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_thigh"].rotate.w;
//		if (angle > glm::radians(-45.0f))
//		{
//			move("left_thigh", glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime)), glm::vec3(-0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		if (done)
//			stage = 1;
//		break;
//	case 1:
//		angle = trans["right_arm"].rotate.w;
//		if (angle < glm::radians(45.0f))
//		{
//			move("right_arm", glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime)), glm::vec3(0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_arm"].rotate.w;
//		if (angle > glm::radians(-45.0f))
//		{
//			move("left_arm", glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime)), glm::vec3(-0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["right_thigh"].rotate.w;
//		if (angle > glm::radians(-45.0f))
//		{
//			move("right_thigh", glm::vec4(1.0f, 0.0f, 0.0f, (angle - speed * deltaTime)), glm::vec3(0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_thigh"].rotate.w;
//		if (angle < glm::radians(45.0f))
//		{
//			move("left_thigh", glm::vec4(1.0f, 0.0f, 0.0f, (angle + speed * deltaTime)), glm::vec3(-0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		if (done)
//			stage = 0;
//		break;
//	}
//}
//
//void Transform::Jump(float deltaTime)
//{
//	float angle;
//	bool done = true;
//
//	switch (stage)
//	{
//	case 0:
//		angle = trans["right_arm"].rotate.w;
//		if (angle > glm::radians(-130.0f))
//		{
//			move("right_arm", glm::vec4(0.0f, 0.0f, 1.0f, (angle - speed * deltaTime)), glm::vec3(0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_arm"].rotate.w;
//		if (angle < glm::radians(130.0f))
//		{
//			move("left_arm", glm::vec4(0.0f, 0.0f, 1.0f, (angle + speed * deltaTime)), glm::vec3(-0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["right_thigh"].rotate.w;
//		if (angle > glm::radians(-30.0f))
//		{
//			move("right_thigh", glm::vec4(0.0f, 0.0f, 1.0f, (angle - speed / 3.0f * deltaTime)), glm::vec3(0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_thigh"].rotate.w;
//		if (angle < glm::radians(30.0f))
//		{
//			move("left_thigh", glm::vec4(0.0f, 0.0f, 1.0f, (angle + speed / 3.0f * deltaTime)), glm::vec3(-0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["right_forearm"].rotate.w;
//		if (angle > glm::radians(-45.0f))
//		{
//			move("right_forearm", glm::vec4(2.0f, 3.0f, 1.0f, (angle - speed * deltaTime)), glm::vec3(0.8627f, -3.163f, 0.2554f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_forearm"].rotate.w;
//		if (angle < glm::radians(45.0f))
//		{
//			move("left_forearm", glm::vec4(-2.0f, 3.0f, 1.0f, (angle + speed * deltaTime)), glm::vec3(-0.8627f, -3.163f, 0.2554f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		if (done)
//			stage = 1;
//		break;
//	case 1:
//		angle = trans["right_arm"].rotate.w;
//		if (angle < glm::radians(10.0f))
//		{
//			move("right_arm", glm::vec4(0.0f, 0.0f, 1.0f, (angle + speed * deltaTime)), glm::vec3(0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_arm"].rotate.w;
//		if (angle > glm::radians(-10.0f))
//		{
//			move("left_arm", glm::vec4(0.0f, 0.0f, 1.0f, (angle - speed * deltaTime)), glm::vec3(-0.5631f, -3.63f, 0.2089f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["right_thigh"].rotate.w;
//		if (angle < glm::radians(5.0f))
//		{
//			move("right_thigh", glm::vec4(0.0f, 0.0f, 1.0f, (angle + speed / 2.0f * deltaTime)), glm::vec3(0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_thigh"].rotate.w;
//		if (angle > glm::radians(-5.0f))
//		{
//			move("left_thigh", glm::vec4(0.0f, 0.0f, 1.0f, (angle - speed / 2.0f * deltaTime)), glm::vec3(-0.2835f, -2.176f, -0.00805f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["right_forearm"].rotate.w;
//		if (angle < glm::radians(0.0f))
//		{
//			move("right_forearm", glm::vec4(2.0f, 3.0f, 1.0f, (angle + speed * deltaTime)), glm::vec3(0.8627f, -3.163f, 0.2554f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		angle = trans["left_forearm"].rotate.w;
//		if (angle > glm::radians(-0.0f))
//		{
//			move("left_forearm", glm::vec4(-2.0f, 3.0f, 1.0f, (angle - speed * deltaTime)), glm::vec3(-0.8627f, -3.163f, 0.2554f), glm::vec3(0, 0, 0));
//			done = false;
//		}
//		if (done)
//			stage = 0;
//		break;
//	}
//}