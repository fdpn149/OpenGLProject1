#include "Mesh.h"
#include <STB/stb_image.h>
#include "Transform.h"

Mesh::Mesh(float vertices[], int size)
{
	mode = 0;
	this->vertices.resize(size / 8);
	memcpy(this->vertices.data(), vertices, size * sizeof(float));
	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices)
{
	mode = 0;
	this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
	setupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material)
{
	mode = 1;
	this->vertices = vertices;
	this->indices = indices;
	this->material = material;
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

void Mesh::draw(Shader& shader)
{
	shader.use();

	shader.setVec3("material.ambient", material.ambient);
	shader.setVec3("material.diffuse", material.diffuse);
	shader.setVec3("material.specular", material.specular);
	shader.setFloat("material.shininess", material.shininess);

	glBindVertexArray(VAO);
	switch (mode)
	{
	case 0: glDrawArrays(GL_TRIANGLES, 0, vertices.size()); break;
	case 1: glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void*)0);
	}
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}
