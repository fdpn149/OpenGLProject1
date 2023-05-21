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

struct TransformTreeNode
{
	std::string name;
	Transform transform;
		
	glm::mat4 finalTransform;

	std::vector<TransformTreeNode*> children;
};

class Model
{
public:
	Model(std::string path);

	std::unordered_map<std::string, TransformTreeNode*> componetMap;
	void Draw(Shader& shader);

	void updateTransforms(const glm::mat4 modelMat);

private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	void readNodeHierachy(TransformTreeNode* node, const glm::mat4 parentTransform);

	std::vector<Mesh> meshes;
	TransformTreeNode* tree;
};

