#include "Plane.h"

#include <vector>
#include <iostream>

#include <STB/stb_image.h>

#include "Mesh.h"

const std::vector<Vertex> TEST =
{
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 5.0f)},
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 5.0f)},
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(5.0f, 0.0f)},

	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(-0.8f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(-0.8f, 0.5f, 0.0f), glm::vec2(5.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(-0.8f, 0.5f, 0.0f), glm::vec2(2.5f, 5.0f)},

	Vertex{glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(5.0f, 0.0f)},
	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(2.5f, 5.0f)},

	Vertex{glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.8f,  0.5f, 0.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.8f,  0.5f, 0.0f), glm::vec2(5.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.8f, 0.5f,  0.0f), glm::vec2(2.5f, 5.0f)},

	Vertex{glm::vec3(0.5f, 0.0f,  0.5f), glm::vec3(0.0f,  0.5f, 0.8f), glm::vec2(5.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(0.0f, 0.8f,  0.0f), glm::vec3(0.0f, 0.5f,  0.8f), glm::vec2(2.5f, 5.0f)},
};

const std::vector<Vertex> PLANE_VERTS =
{
	Vertex{ glm::vec3(-100.0f, 0.0f,  100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
	Vertex{ glm::vec3(-100.0f, 0.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 25.0f) },
	Vertex{ glm::vec3( 100.0f, 0.0f, -100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(25.0f, 25.0f) },
	Vertex{ glm::vec3( 100.0f, 0.0f,  100.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(25.0f, 0.0f) }
};

const std::vector<unsigned int> PLANE_INDICES =
{
	0, 1, 2,
	0, 2, 3
};

Plane::Plane(const std::string& diffuseTex, const std::string& specularTex)
{
	initBufferObjects();

	diffuseTexId = loadTexture(diffuseTex);
	specularTexId = loadTexture(specularTex);
}

void Plane::draw(Shader& shader)
{
	shader.use();

	// activate diffuse
	shader.setInt("material.diffuse", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTexId);

	// activate specular
	shader.setInt("material.specular", 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularTexId);

	shader.setFloat("material.shininess", 32.0f);

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, PLANE_INDICES.size(), GL_UNSIGNED_INT, (void*)0);
}

void Plane::initBufferObjects()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * PLANE_VERTS.size(), PLANE_VERTS.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * PLANE_INDICES.size(), PLANE_INDICES.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	// unbind buffer objects
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int Plane::loadTexture(const std::string& path)
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

	// load image
	int width, height, channelNum;
	unsigned char* imageBytes = stbi_load(path.c_str(), &width, &height, &channelNum, 0);
	if (imageBytes)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageBytes);

		stbi_image_free(imageBytes);
	}
	else
	{
		std::cout << "Cubemap tex failed to load at path: "  << std::endl;
		stbi_image_free(imageBytes);
	}

	// generate mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	// unbind texture object
	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}
