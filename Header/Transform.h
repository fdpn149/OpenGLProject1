#pragma once
#include <glm/glm.hpp>
#include <string>
#include <map>

//struct Node
//{
//	std::string name;
//	Node* parent;
//};

class Transform
{
	//static void move(std::string part, glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate);
	//static int stage;
	//static float speed;
public:
	glm::vec4 rotate;
	glm::vec3 offset;
	glm::vec3 translate;

	//static std::map<std::string, Transform> trans;
	//
	Transform();
	Transform(glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate);

	void set(glm::vec4 rotate, glm::vec3 offset, glm::vec3 translate);

	//static void HierarchyTrans(glm::mat4& modelMat, Node* node);
	//static void Idle();
	//static void Walk(float deltaTime);
	//static void Jump(float deltaTime);
};

