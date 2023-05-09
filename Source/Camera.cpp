#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	this->position = position;
	this->worldUp = worldUp;
	this->forward = glm::normalize(position - target);
	this->right = glm::normalize(glm::cross(target, worldUp));
	this->up = glm::normalize(glm::cross(right, target));
	this->pitch = 0;
	this->yaw = 0;
}

Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldUp)
{
	this->position = position;
	this->worldUp = worldUp;
	this->pitch = pitch;
	this->yaw = yaw;
	forward.x = glm::cos(pitch) * glm::sin(yaw);
	forward.y = glm::sin(pitch);
	forward.z = glm::cos(pitch) * glm::cos(yaw);
	forward = glm::normalize(forward);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));
}

int Camera::processInput(GLFWwindow* window, float deltaTime)
{
	float cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return -1;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position -= cameraSpeed * forward;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position += cameraSpeed * forward;

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position -= cameraSpeed * right;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position += cameraSpeed * right;

	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		position += cameraSpeed * up;
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		position -= cameraSpeed * up;

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		return 1;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		return 2;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		return 3;
	return 0;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(position, position - forward, worldUp);
}

void Camera::onMousePositionChanged(double xPos, double yPos, bool& firstMouse)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = lastX - xPos;
	float yOffset = yPos - lastY;

	lastX = xPos;
	lastY = yPos;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;


	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * cos(glm::radians(yaw));

	forward = glm::normalize(front);
	right = glm::normalize(glm::cross(forward, worldUp));
	up = glm::normalize(glm::cross(right, forward));
}
