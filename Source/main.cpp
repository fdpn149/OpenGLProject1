#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define SIZEOF(x) (sizeof(box_vertices) / sizeof(float))
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include "../Header/Material.h"
#include "../Header/Mesh.h"
#include "../Header/Shader.h"
#include "../Header/Camera.h"
#include "../Header/Light.h"
#include "../Header/Model.h"
#include "../Header/Transform.h"

void initGLFW();
GLFWwindow* initWindow();
void initGLEW();

Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0, 1.0f, 0));

float box_vertices[] = {
	// positions         // normals       // texture coords
	-0.5f,  -0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f,  -0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,   0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,   0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,   0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f,  -0.5f,  -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f,  -0.5f,   0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f,  -0.5f,   0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,   0.5f,   0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,   0.5f,   0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,   0.5f,   0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f,  -0.5f,   0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,   0.5f,   0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,   0.5f,  -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f,  -0.5f,  -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f,  -0.5f,  -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f,  -0.5f,   0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,   0.5f,   0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,   0.5f,   0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,   0.5f,  -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  -0.5f,  -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  -0.5f,  -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  -0.5f,   0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,   0.5f,   0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f,  -0.5f,  -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  -0.5f,  -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  -0.5f,   0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  -0.5f,   0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  -0.5f,   0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  -0.5f,  -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,   0.5f,  -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,   0.5f,  -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,   0.5f,   0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,   0.5f,   0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,   0.5f,   0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,   0.5f,  -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xPos, double yPos);

int main()
{
	initGLFW();
	GLFWwindow* window = initWindow();
	initGLEW();

	glEnable(GL_DEPTH_TEST);

	Light light = Light(glm::vec3(1.5f, 1.5f, 1.5f),
		glm::vec3(glm::radians(90.0f), glm::radians(90.0f), 0), glm::vec3(1.0f, 1.0f, 1.0f));
	Shader shader("../Shader/proj1.vert", "../Shader/proj1.frag");
	Mesh mesh(box_vertices, SIZEOF(box_vertices));
	Material material(&shader, mesh.loadImageToGPU("../Textures/container2.png", GL_RGBA, GL_RGBA, 0),
		mesh.loadImageToGPU("../Textures/container2_specular.png", GL_RGBA, GL_RGBA, 1),
		glm::vec3(0.3f, 0.3f, 0.3f),
		32.0f);
	Model model("../Model/robot4/robot4.obj");

	glm::mat4 modelMat = glm::mat4(1.0f);
	glm::mat4 viewMat;
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0, 0.0f));
	modelMat = glm::scale(modelMat, glm::vec3(0.2, 0.2, 0.2));
	shader.use();
	shader.setMat4("model", modelMat);

	int mode = 1;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		int temp = camera.processInput(window, deltaTime);
		if (temp > 0)
		{
			if(mode != temp)
				Transform::Idle();
			mode = temp;
		}

		switch (mode)
		{
		case 1:
			Transform::Idle();	break;
		case 2:
			Transform::Walk(deltaTime);	break;
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		viewMat = camera.getViewMatrix();

		shader.use();
		shader.setMat4("view", viewMat);
		shader.setMat4("projection", projMat);

		shader.setVec3("light.pos", light.position);
		shader.setVec3("light.color", light.color);

		shader.setVec3("material.ambient", material.ambient);
		shader.setInt("material.diffuse", 0);
		shader.setInt("material.specular", 1);
		shader.setFloat("material.shininess", 64.0f);

		shader.setVec3("cameraPos", camera.position);

		mesh.draw(&shader);	//Draw Box
		model.Draw(material.shader);	//Draw Model

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void initGLFW()
{
	if (glfwInit() == GL_FALSE)
	{
		printf("GLFW failed.");
		exit(-1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* initWindow()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "Project1", NULL, NULL);
	if (window == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(window);

	glViewport(0, 0, 800, 600);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);

	return window;
}

void initGLEW()
{
	if (glewInit() != GLEW_OK)
	{
		printf("Init GLEW failed.");
		glfwTerminate();
		exit(-1);
	}
}

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	camera.onMousePositionChanged(xPos, yPos, firstMouse);
}