#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Transform.h"

struct NewNode
{
	std::string name;
	Transform transform;
		
	glm::mat4 finalTransform;

	std::vector<NewNode*> children;
};

class Model
{
public:
	Model(std::string path);
	~Model();
	std::map<std::string, Node*> inherit;
	std::vector<Mesh> meshes;
	std::string directory;
	std::unordered_map<std::string, NewNode*> componetMap;

	void updateTransforms(const glm::mat4 modelMat);
	void readNodeHierachy(NewNode* node, const glm::mat4 parentTransform);

	void Draw(Shader* shader);
private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	NewNode* tree;
};

