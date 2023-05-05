#pragma once
#include "../Header/Mesh.h"
#include "Shader.h"
class Model2
{
	Mesh* newMesh;
public:
	Model2();
	void draw(Shader* shader);
	~Model2();
};

