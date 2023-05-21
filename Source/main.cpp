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

#include "Skybox.h"
#include "Plane.h"
#include "Grass.h"

enum class AnimationType
{
	WALK,
	JACKPOT,
	MOON_WALK,
	SQUAT,
	SIT_UP,
	PUSH_UP,
	GANGNAM_STYLE,
	MAX
};


Camera camera(glm::vec3(0, 2.5f, 10.0f), glm::radians(0.0f), glm::radians(0.0f), glm::vec3(0, 1.0f, 0));

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

void initGLFW();
GLFWwindow* initWindow();
void initGLEW();
void mouseCallback(GLFWwindow* window, double xPos, double yPos);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
Animation* getAnimationByType(Model& model, float speed, AnimationType type);

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
	
	// light
	Light light(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(1.0f), glm::vec3(1.0f));

	// skybox
	Skybox skybox("../Skybox/");

	// shaders
	Shader shader("../Shader/proj1.vert", "../Shader/proj1.frag");
	Shader textureShader("../Shader/texture.vert", "../Shader/texture.frag");
	Shader skyboxShader("../Shader/skybox.vert", "../Shader/skybox.frag");

	Shader grassShader("../Shader/grass.vert", "../Shader/grass.frag", "../Shader/grass.geom");

	// box mesh
	Mesh mesh(box_vertices, SIZEOF(box_vertices));

	// plane 
	Plane plane("../Textures/grass_diffuse.jpg", "../Textures/grass_specular.jpg");

	// grass
	Grass grass("../Textures/grass_atlas.png", "../Textures/wind.jpg");

	// robot model
	Model model("../Model/robot/robot.obj");

	// projection matrix
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);;
	
	// dropdown menu informations
	float speed = 1.0f;

	int currentComboItem = 0;
	AnimationType currentAnimationType = AnimationType::SQUAT;

	const char* animations[] = { "Walk", "Jackpot", "MoonWalk", "Squat", "Sit-up", "PushUp", "GangnamStyle" };

	// model matrix
	glm::mat4 grassModelMat = glm::mat4(1.0f);
	grassModelMat = glm::scale(grassModelMat, glm::vec3(1.0f, 1.0f, 1.0f));

	// anmation
	Animation* currentAnimation;
	currentAnimation = new SquatAnimation(model, speed);

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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Skybox
		//-------
		skyboxShader.use();
		skyboxShader.setMat4("view", glm::mat4(glm::mat3(camera.getViewMatrix())));
		skyboxShader.setMat4("projection", projMat);

		// draw skybox
		skybox.draw(skyboxShader);

		// Grass
		//------
		grassShader.use();
		grassShader.setMat4("view", camera.getViewMatrix());
		grassShader.setMat4("projection", projMat);

		// wind time
		grassShader.setFloat("time", lastFrame);
		
		grass.draw(grassShader);


		// Plane
		//------
		textureShader.use();
		textureShader.setMat4("view", camera.getViewMatrix());
		textureShader.setMat4("projection", projMat);
		textureShader.setMat4("model", grassModelMat);

		// set camera position
		textureShader.setVec3("cameraPos", camera.position);

		// set light
		light.setLight2Shader(textureShader);

		// draw texture objects
		plane.draw(textureShader);


		// Model
		//------
		shader.use();
		shader.setMat4("view", camera.getViewMatrix());
		shader.setMat4("projection", projMat);
		shader.setMat4("model", glm::mat4(1.0f));

		// set camera position
		shader.setVec3("cameraPos", camera.position);

		// set light
		light.setLight2Shader(shader);
		
		// draw calls
		model.Draw(shader);


		// GUI
		//----
		ImGui::Begin("Window");
		ImGui::Combo("Animations", &currentComboItem, animations, sizeof(animations) / sizeof(char*));
		ImGui::SliderFloat("Speed", &speed, 0.0f, 5.0f);
		ImGui::End();

		// check if user has select different animation
		if (static_cast<AnimationType>(currentComboItem) != currentAnimationType)
		{
			currentAnimationType = static_cast<AnimationType>(currentComboItem);
			delete currentAnimation;
			currentAnimation = getAnimationByType(model, speed, currentAnimationType);
		}

		currentAnimation->setSpeed(speed);

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Project1", NULL, NULL);
	if (window == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();
		exit(-1);
	}

	// make context
	glfwMakeContextCurrent(window);

	// diable cursor visiability
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// callbacks
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

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

void mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	camera.onMousePositionChanged(xPos, yPos);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Animation* getAnimationByType(Model& model, float speed, AnimationType type)
{
	switch (type)
	{
	case AnimationType::WALK:
		return new WalkAnimation(model, speed);

	case AnimationType::JACKPOT:
		return new JackpotAnimation(model, speed);

	case AnimationType::MOON_WALK:
		return new MoonWalkAnimation(model, speed);

	case AnimationType::SQUAT:
		return new SquatAnimation(model, speed);

	case AnimationType::SIT_UP:
		return new SitupAnimation(model, speed);

	case AnimationType::PUSH_UP:
		return new PushUpAnimation(model, speed);

	case AnimationType::GANGNAM_STYLE:
		return new GangnamAnimation(model, speed);

	case AnimationType::MAX:
		return nullptr;

	default:
		return nullptr;
	}
}