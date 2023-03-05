#include "cube.h"

Kasumi::CubeObject::CubeObject()
{
	NAME = "Cube" + std::to_string(ID);
	MESH = "cube";
	_shader = Shader::DefaultMeshShader;
	_collider = std::make_shared<HinaPE::Geom::RigidBodyCollider3>(std::make_shared<HinaPE::Geom::Box3>(_opt.width, _opt.height, _opt.depth));
	_init();
}
void Kasumi::CubeObject::INSPECT()
{
	ObjectMesh3D::INSPECT();

	ImGui::Text("init width: %f", _opt.width);
	ImGui::Text("init height: %f", _opt.height);
	ImGui::Text("init depth: %f", _opt.depth);
}
void Kasumi::CubeObject::sync_opt()
{
	if (!_dirty)
		return;

	POSE.scale.x() = _opt.width;
	POSE.scale.y() = _opt.height;
	POSE.scale.z() = _opt.depth;

	_dirty = false;
}
