#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>
#include "Shader.h"
#include "Transform.h"
#include "Material.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

class Mesh
{
	unsigned int VAO, VBO, EBO;
	int size;
	int mode;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	Material material;
	void setupMesh();
public:
	Node* node = nullptr;
	Transform transform;
	Mesh(float vertices[], int size);
	Mesh(std::vector<Vertex> vertices);
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material);
	void draw(Shader* shader);
};

