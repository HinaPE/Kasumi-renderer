#include "cup.h"
Kasumi::CupObject::CupObject()
{
	NAME = "Cup" + std::to_string(ID);
	MESH = "cup";
	_shader = Shader::DefaultMeshShader;
	_init();
}
