#include "cloth.h"

void Kasumi::ClothObject::init(std::vector<Mesh::Vertex> &&vertices, std::vector<Mesh::Index> &&indices, std::map<std::string, std::vector<TexturePtr>> &&textures)
{
	_mesh = std::make_shared<Mesh>(std::move(vertices), std::move(indices), std::move(textures));
}
