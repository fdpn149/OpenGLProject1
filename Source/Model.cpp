#include "../Header/Model.h"
#include "../Include/STB/stb_image.h"

Model::Model(std::string path)
{
	loadModel(path);
}

Model::~Model()
{
	for (auto i : inherit)
	{
		delete i.second;
	}
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
	//const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		printf("Assimp error\n");
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
		if (count > 1)
			printf("");
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
	}
	
	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];
		Mesh newMesh = processMesh(curMesh, scene);
		if (inherit.find(name) != inherit.end())
		{
			newMesh.node = inherit[name];
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
	std::vector<Texture> textures;

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
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh({ tempVertices,tempIndices,{} });
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{  
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture); 
		}
	}
	return textures;
}

unsigned int Model::TextureFromFile(const char* path, const std::string& directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		printf("Texture failed to load at path: %s\n", path);
		stbi_image_free(data);
	}

	return textureID;
}