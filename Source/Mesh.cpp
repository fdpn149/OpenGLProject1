#include "../Header/Mesh.h"
#include <STB/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>

Mesh::Mesh(float vertices[], int size)
{
	mode = 0;
	this->vertices.resize(size / 8);
	memcpy(this->vertices.data(), vertices, size * sizeof(float));
	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	mode = 1;
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

	glBindVertexArray(0);
}

void Mesh::hierarchyTrans(glm::mat4& modelMat, Node* node)
{
	if (node != nullptr)
	{
		Node* tempNode = node->parent;
		hierarchyTrans(modelMat, tempNode);
		if (Transform::trans.find(node->name) != Transform::trans.end())
		{
			modelMat = glm::translate(modelMat, -Transform::trans[node->name].translate);
			modelMat = glm::rotate(modelMat, Transform::trans[node->name].rotate.w, glm::vec3(Transform::trans[node->name].rotate));
			modelMat = glm::scale(modelMat, Transform::trans[node->name].scale);
			modelMat = glm::translate(modelMat, Transform::trans[node->name].translate);
		}
	}
}


void Mesh::draw(Shader* shader)
{
	glm::mat4 modelMat = glm::mat4(1.0f);

	hierarchyTrans(modelMat, node);

	shader->use();
	shader->setMat4("model", modelMat);

	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == "texture_diffuse")
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->setInt("material.diffuse", 0);
		}
		else if (textures[i].type == "texture_specular")
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			shader->setInt("material.specular", 1);
		}
	}

	glBindVertexArray(VAO);
	switch (mode)
	{
	case 0: glDrawArrays(GL_TRIANGLES, 0, 36); break;
	case 1: glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

GLuint Mesh::loadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot)
{
	GLuint TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture\n");
	}
	stbi_image_free(data);
	return TexBuffer;
}