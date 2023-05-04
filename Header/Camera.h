#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 worldUp;
	glm::vec3 forward, right, up;
	float pitch = 0, yaw = 0;
	float sensitivity = 0.1f;
	float lastX, lastY;

	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp);
	void processInput(GLFWwindow* window, float deltaTime);
	glm::mat4 getViewMatrix();
	void onMousePositionChanged(double xPos, double yPos, bool& firstMouse);
};

