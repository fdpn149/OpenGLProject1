#pragma once	

#include <vector>

#include "Mesh.h"

class Primitive
{
public:
	Primitive();
	virtual ~Primitive();

private:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};