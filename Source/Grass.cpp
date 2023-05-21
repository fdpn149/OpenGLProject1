#include "Grass.h"

#include <vector>
#include <string>
#include <iostream>
#include <random>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <STB/stb_image.h>

struct GrassTypes
{
	glm::vec3 position;
	int type;
};

Grass::Grass(const std::string& grassTex, const std::string& windTex)
{	
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> rand8(1, 8);

	// init positions
	std::vector<GrassTypes> grassList;
	for (float x = -100.0f; x < 100.0f; x += 0.5f)
	{
		for (float z = -100.0f; z < 100.0f; z += 0.5f)
		{
			grassList.push_back(GrassTypes{ glm::vec3(x, 0, z), static_cast<int>(rand8(rng)) });
		}
	}

	vertexNum = grassList.size();
	

    // init buffer objects
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GrassTypes) * vertexNum, grassList.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GrassTypes), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribIPointer(1, 1, GL_INT, sizeof(GrassTypes), (void*)offsetof(GrassTypes, type));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // init texture
	grassTexId = loadTexture(grassTex);
	windTexId = loadTexture(windTex);
}

void Grass::draw(Shader& shader)
{
	shader.use();

	shader.setInt("grassTex", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, grassTexId);

	shader.setInt("wind", 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, windTexId);

	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, vertexNum);
}

unsigned int Grass::loadTexture(const std::string& path)
{
	unsigned int id;

	// initialize OpenGL texture
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	// configure the type of algorithm for the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// configure the way to repeat texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	stbi_set_flip_vertically_on_load(false);

	// load image
	int width, height, channelNum;
	unsigned char* imageBytes = stbi_load(path.c_str(), &width, &height, &channelNum, 0);
	if (imageBytes)
	{
		GLenum format;
		if (channelNum == 1)
			format = GL_RED;
		else if (channelNum == 3)
			format = GL_RGB;
		else if (channelNum == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageBytes);

		stbi_image_free(imageBytes);
	}
	else
	{
		std::cout << "Cubemap tex failed to load at path: " << std::endl;
		stbi_image_free(imageBytes);
	}

	// generate mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	// unbind texture object
	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}