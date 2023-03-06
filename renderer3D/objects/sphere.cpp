#include "sphere.h"
Kasumi::SphereObject::SphereObject()
{
	NAME = "Sphere";
	_shader = Shader::DefaultMeshShader;
	_init("sphere", "");
}
void Kasumi::SphereObject::sync_opt()
{
	POSE.scale.x() = _opt.radius;
	POSE.scale.y() = _opt.radius;
	POSE.scale.z() = _opt.radius;
	_dirty = true;
}
