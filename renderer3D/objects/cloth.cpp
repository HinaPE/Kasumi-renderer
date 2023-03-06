//#include "cloth.h"
//
//Kasumi::ClothObject::ClothObject()
//{
//	NAME = "Cloth";
//	_shader = Shader::DefaultMeshShader;
//}
//void Kasumi::ClothObject::init(std::vector<Mesh::Vertex> &&vertices, std::vector<Mesh::Index> &&indices, std::map<std::string, std::vector<TexturePtr>> &&textures)
//{
//	_mesh = std::make_shared<Mesh>(std::move(vertices), std::move(indices), std::move(textures));
//}
//void Kasumi::ClothObject::update(const std::vector<mVector3> &new_vertices)
//{
//	auto &_v = _mesh->vertices();
//	assert(_v.size() == new_vertices.size());
//	for (int i = 0; i < _v.size(); ++i)
//		_v[i].position = new_vertices[i];
//}
