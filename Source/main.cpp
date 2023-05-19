#define GLEW_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define SIZEOF(x) (sizeof(box_vertices) / sizeof(float))
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <STB/stb_image.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Transform.h"
#include "WalkAnimation.h"
#include "JackpotAnimation.h"
#include "SquatAnimation.h"
#include "MoonWalkAnimation.h"
#include "SitupAnimation.h"
#include "PushUpAnimation.h"
#include "GangnamAnimation.h"

void initGLFW();
GLFWwindow* initWindow();
void initGLEW();

Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0, 1.0f, 0));

float box_vertices[] = {
	// positions         // normals       // texture coords
	-0.5f,  -0.05f,  -0.05f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f,  -0.05f,  -0.05f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,   0.05f,  -0.05f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,   0.05f,  -0.05f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,   0.05f,  -0.05f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f,  -0.05f,  -0.05f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f,  -0.05f,   0.05f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f,  -0.05f,   0.05f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,   0.05f,   0.05f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,   0.05f,   0.05f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,   0.05f,   0.05f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f,  -0.05f,   0.05f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,   0.05f,   0.05f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,   0.05f,  -0.05f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f,  -0.05f,  -0.05f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f,  -0.05f,  -0.05f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f,  -0.05f,   0.05f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,   0.05f,   0.05f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,   0.05f,   0.05f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,   0.05f,  -0.05f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  -0.05f,  -0.05f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  -0.05f,  -0.05f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  -0.05f,   0.05f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,   0.05f,   0.05f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f,  -0.05f,  -0.05f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  -0.05f,  -0.05f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  -0.05f,   0.05f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  -0.05f,   0.05f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  -0.05f,   0.05f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  -0.05f,  -0.05f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,   0.05f,  -0.05f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,   0.05f,  -0.05f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,   0.05f,   0.05f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,   0.05f,   0.05f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,   0.05f,   0.05f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,   0.05f,  -0.05f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xPos, double yPos);

int main()
{
	initGLFW();
	GLFWwindow* window = initWindow();
	initGLEW();

	glEnable(GL_DEPTH_TEST);

	// init dear imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
	

	Light light = Light(glm::vec3(1.5f, 40.0f, 1.5f),
		glm::vec3(glm::radians(90.0f), glm::radians(90.0f), 0), glm::vec3(2.0f, 2.0f, 2.0f));

	Shader shader("../Shader/proj1.vert", "../Shader/proj1.frag");

	Mesh mesh(box_vertices, SIZEOF(box_vertices));

	Model model("../Model/robot/robot.obj");

	Animation* currentAnimation;
	currentAnimation = new GangnamAnimation(model, 2.0f);
		
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0, 0.0f));
	modelMat = glm::scale(modelMat, glm::vec3(0.2, 0.2, 0.2));

	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	shader.use();
	int mode = 1;
	while (!glfwWindowShouldClose(window))
	{
		// process time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// process input
		camera.processInput(window, deltaTime);

		// update animation
		currentAnimation->update(deltaTime);

		// start imgui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// set background color
		glClearColor(0.0f, 0.125f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		// set matrices
		shader.setMat4("view", camera.getViewMatrix());
		shader.setMat4("projection", projMat);
		shader.setMat4("model", glm::mat4(1.0f));

		// set light
		shader.setVec3("light.pos", light.position);
		shader.setVec3("light.color", light.color);

		// set camera position
		shader.setVec3("cameraPos", camera.position);

		// draw calls
		mesh.draw(&shader);	//Draw Box
		model.Draw(&shader); //Draw Model

		// set imgui ui
		ImGui::Begin("Window");
		ImGui::Text("Hellow world!");
		ImGui::End();

		// render imgui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete currentAnimation;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

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
	camera.onMousePositionChanged(xPos, yPos);
}