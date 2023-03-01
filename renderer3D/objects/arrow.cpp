#include "arrow.h"

void Kasumi::ArrowObject::INSPECT()
{
	ObjectMesh3D::INSPECT();

	ImGui::Text("init origin: %f %f %f", _opt.origin.x(), _opt.origin.y(), _opt.origin.z());
	ImGui::Text("init direction: %f %f %f", _opt.direction.x(), _opt.direction.y(), _opt.direction.z());
}
Kasumi::ArrowObject::ArrowObject()
{
	NAME = "Arrow" + std::to_string(ID);
	MESH = "arrow";
	_shader = Shader::DefaultMeshShader;
	init();
}
void Kasumi::ArrowObject::sync_opt()
{
	if (!_dirty)
		return;

	_pose.position = _opt.origin;
	_pose.euler = mQuaternion(mVector3(0, 0, 1), _opt.direction).euler();
	_pose.scale = mVector3(0.2, 0.3, 0.2);
}
