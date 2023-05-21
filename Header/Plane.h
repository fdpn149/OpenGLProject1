#pragma once

#include <string>

#include "Shader.h"

class Plane
{
public:
	Plane(const std::string& diffuseTex, const std::string& specularTex);

	void draw(Shader& shader);

private:
	void initBufferObjects();

	unsigned int loadTexture(const std::string& path);

private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

	unsigned int diffuseTexId;
	unsigned int specularTexId;
};