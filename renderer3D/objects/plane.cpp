#include "plane.h"

Kasumi::PlaneObject::PlaneObject()
{
	NAME = "Plane";
	_shader = Shader::DefaultMeshShader;
	_init("plane", "");
	load_surface(this);
}
