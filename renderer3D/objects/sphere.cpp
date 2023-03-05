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
	POSE.scale.x() = _opt.radius;
	POSE.scale.y() = _opt.radius;
	POSE.scale.z() = _opt.radius;
	_dirty = true;
}
