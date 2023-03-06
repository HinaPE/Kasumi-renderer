#include "cube.h"

Kasumi::CubeObject::CubeObject()
{
	NAME = "Cube";
	_shader = Shader::DefaultMeshShader;
	_init("cube", "");
	load_surface(this);
}
