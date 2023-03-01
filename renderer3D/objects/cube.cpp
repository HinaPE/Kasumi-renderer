#include "cube.h"

Kasumi::CubeObject::CubeObject()
{
	NAME = "Cube" + std::to_string(ID);
	MESH = "cube";
	_shader = Shader::DefaultMeshShader;
	init();
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

	_pose.scale.x() = _opt.width;
	_pose.scale.y() = _opt.height;
	_pose.scale.z() = _opt.depth;

	_dirty = false;
}
