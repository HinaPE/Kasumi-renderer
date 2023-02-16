#ifndef KASUMI_CLOTH_H
#define KASUMI_CLOTH_H

#include "object3D.h"

namespace Kasumi
{
class ClothObject final : public ObjectMesh3D
{
public:
	ClothObject() { NAME = "cloth"; }
	void init(std::vector<Mesh::Vertex> &&vertices, std::vector<Mesh::Index> &&indices, std::map<std::string, std::vector<TexturePtr>> &&textures);
	void update(const std::vector<mVector3> &new_vertices)
	{
		auto &_v = _mesh->vertices();
		assert(_v.size() == new_vertices.size());
		for (int i = 0; i < _v.size(); ++i)
			_v[i].position = new_vertices[i];
	}
};
using ClothObjectPtr = std::shared_ptr<ClothObject>;
} // namespace Kasumi

#endif //KASUMI_CLOTH_H
