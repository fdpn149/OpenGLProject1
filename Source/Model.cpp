#include "Model.h"
#include <STB/stb_image.h>

#include <iostream>
#include <sstream>

Model::Model(std::string path)
{
	tree = nullptr;
	componetMap = {};
	loadModel(path);
}

Model::~Model()
{
	for (auto i : inherit)
	{
		delete i.second;
	}
}

void Model::updateTransforms(const glm::mat4 modelMat)
{
	readNodeHierachy(tree, modelMat);
}


void Model::readNodeHierachy(NewNode* node, const glm::mat4 parentTransform)
{
	node->finalTransform = glm::translate(parentTransform, node->transform.translate);
	node->finalTransform = glm::translate(node->finalTransform, -node->transform.offset);
	node->finalTransform = glm::rotate(node->finalTransform, node->transform.rotate.w, glm::vec3(node->transform.rotate));
	node->finalTransform = glm::translate(node->finalTransform, node->transform.offset);

	for (int iii = 0; iii < node->children.size(); ++iii)
	{
		readNodeHierachy(node->children[iii], node->finalTransform);
	}
}

void Model::Draw(Shader* shader)
{
	for (GLuint i = 0; i < meshes.size(); i++)
	{
		shader->use();
		shader->setMat4("model", componetMap[meshes[i].componet]->finalTransform);

		meshes[i].draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;

	//const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	std::string name;
	name = node->mName.C_Str();

	int count = std::count(name.begin(), name.end(), ':');

	if (count > 0)
	{
		std::stringstream sstream(name);

		NewNode* currentNode = tree;

		while (!sstream.eof())
		{
			std::string componetName;
			sstream >> componetName;

			componetName = componetName.substr(6);

			std::cout << componetName << std::endl;

			// handle robot base
			if (componetName == "body_base")
			{
				if (currentNode == nullptr)
				{
					currentNode = new NewNode({ componetName, Transform(), {} });

					tree = currentNode;

					componetMap.insert({ componetName, currentNode });
				}
			}
			else
			{
				bool found = false;

				NewNode* nextNode = nullptr;

				// find if componet already exit
				for (auto it = currentNode->children.begin(); it < currentNode->children.end(); ++it)
				{
					if ((*it)->name == componetName)
					{
						nextNode = (*it);
						found = true;
					}
				}

				// set current node
				if (found)
				{
					currentNode = nextNode;
				}
				// add new componet
				else
				{
					NewNode* newNode = new NewNode({ componetName, Transform(), {} });

					currentNode->children.push_back(newNode);

					componetMap.insert({ componetName, newNode });
				}

			}

		}

		unsigned int index = name.find_last_of(':');
		name = name.substr(index + 1, name.length() - 1);
		inherit[name] = new Node({ name, nullptr });

		if (count > 1)
		{
			std::string current = name;
			name = node->mName.C_Str();
			name = name.substr(0, index);

			index = name.find_last_of(':');
			unsigned int index2 = name.find_last_of(' ');
			name = name.substr(index + 1, index2 - index - 1);
			inherit[current]->parent = inherit[name];
			name = current;
		}

		Transform::trans[name]; //?
	}

	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
		Mesh newMesh = processMesh(curMesh, scene);
		if (inherit.find(name) != inherit.end())
		{
			newMesh.node = inherit[name];
			newMesh.componet = name;
		}

		meshes.push_back(newMesh);
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<GLuint> tempIndices;
	Material tempMaterial;

	glm::vec3 tempVec;
	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex tempVertex;
		tempVertex.position.x = mesh->mVertices[i].x;
		tempVertex.position.y = mesh->mVertices[i].y;
		tempVertex.position.z = mesh->mVertices[i].z;

		tempVertex.normal.x = mesh->mNormals[i].x;
		tempVertex.normal.y = mesh->mNormals[i].y;
		tempVertex.normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			tempVertex.texCoord.x = mesh->mTextureCoords[0][i].x;
			tempVertex.texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			tempVertex.texCoord = glm::vec2(0);
		}

		tempVertices.push_back(tempVertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		for (GLuint j = 0; j < mesh->mFaces[i].mNumIndices; j++)
		{
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiColor3D color;
		material->Get(AI_MATKEY_COLOR_AMBIENT, color);
		tempMaterial.ambient = glm::vec3(color.r, color.g, color.b);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		tempMaterial.diffuse = glm::vec3(color.r, color.g, color.b);
		material->Get(AI_MATKEY_COLOR_SPECULAR, color);
		tempMaterial.specular = glm::vec3(color.r, color.g, color.b);

	}
	return Mesh({ tempVertices,tempIndices,tempMaterial });
}

