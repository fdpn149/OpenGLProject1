#include "../Header/Model2.h"
#include <fstream>
#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

Model2::Model2()
{
	ifstream inputStream;
	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;

	vector<Vertex> toMesh;

	float v0, v1, v2;
	string s0, s1, s2;

	vertices.resize(1);
	uvs.resize(1);
	normals.resize(1);

	inputStream.open("../Model/robot.obj");
	while (inputStream >> s0 && s0 != "mtllib");
	inputStream >> s0;
	while (inputStream >> s0)
	{
		if (s0 == "g")
		{
			inputStream >> s0;
		}
		else if (s0 == "v")
		{
			inputStream >> v0 >> v1 >> v2;
			vertices.push_back(vec3(v0, v1, v2));
		}
		else if (s0 == "vt")
		{
			inputStream >> v0 >> v1;
			uvs.push_back(vec2(v0, v1));
		}
		else if (s0 == "vn")
		{
			inputStream >> v0 >> v1 >> v2;
			normals.push_back(vec3(v0, v1, v2));
		}
		else if (s0 == "f")
		{
			string ss[3];
			inputStream >> ss[0] >> ss[1] >> ss[2];
			for (int i = 0; i < 3; i++)
			{
				int x, y, z;
				const char* test[100];
				sscanf_s(ss[i].c_str(), "%d/%d/%d", &x, &y, &z);

				toMesh.push_back({ vertices[x],normals[z],uvs[y] });
			}
		}
	}

	newMesh = new Mesh(toMesh);
}

void Model2::draw(Shader* shader)
{
	newMesh->draw(shader);
}

Model2::~Model2()
{
	delete newMesh;
}
