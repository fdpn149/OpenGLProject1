#include "../Header/Model.h"
#include "../Include/STB/stb_image.h"

Model::Model(std::string path)
{
	loadModel(path);
}

void Model::Draw(Shader* shader)
{
	for (GLuint i = 0; i < meshes.size(); i++)
	{
		meshes[i].draw(shader);
	}
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("Assimp error\n");
		return;
	}
	directory = path.substr(0, path.find_last_of('/'));
	//printf("Success! %s\n", directory.c_str());
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(curMesh, scene));
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
	//std::vector<Texture> tempTextures;

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
	return Mesh({ tempVertices,tempIndices,{} });
}
