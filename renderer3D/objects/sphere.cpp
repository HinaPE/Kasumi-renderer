#include "sphere.h"
Kasumi::SphereObject::SphereObject()
{
	NAME = "Sphere" + std::to_string(ID);
	MESH = "sphere";
	_shader = Shader::DefaultMeshShader;
	_init();
}
void Kasumi::SphereObject::sync_opt()
{
	_pose.scale.x() = _opt.radius;
	_pose.scale.y() = _opt.radius;
	_pose.scale.z() = _opt.radius;
	_dirty = true;
}
