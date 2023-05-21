#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "Shader.h"

class Grass
{
public:
	Grass(const std::string& grassTex, const std::string& windTex);

	void draw(Shader& shader);

private:
	void setPositions(std::vector<glm::vec3>& positions);
	unsigned int loadTexture(const std::string& path);

private:
	int vertexNum;

	unsigned int vao;
	unsigned int vbo;
	unsigned int grassTexId;
	unsigned int windTexId;
};