#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include "Shader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
	unsigned int VAO, VBO, EBO;
	int size;
	int mode;
	void setupMesh();
public:
	Mesh(float vertices[], int size);
	Mesh(std::vector<Vertex> vertices);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	void draw(Shader* shader);
	GLuint loadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot);
};

