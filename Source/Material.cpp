#include "..\Header\Material.h"

Material::Material()
{}

Material::Material(glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _ambient, float _shininess)
	: diffuse(_diffuse), specular(_specular), ambient(_ambient), shininess(_shininess)
{}
