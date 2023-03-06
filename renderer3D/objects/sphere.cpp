#include "sphere.h"
Kasumi::SphereObject::SphereObject()
{
	NAME = "Sphere";
	_shader = Shader::DefaultMeshShader;
	_init("sphere", "");
	load_surface(this);
}
void Kasumi::SphereObject::sync_opt()
{
	POSE.scale.x() = _radius;
	POSE.scale.y() = _radius;
	POSE.scale.z() = _radius;
	_dirty = true;
}
