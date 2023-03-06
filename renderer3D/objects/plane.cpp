#include "plane.h"

Kasumi::PlaneObject::PlaneObject()
{
	NAME = "Plane";
	_shader = Shader::DefaultMeshShader;
	_init("plane", "");
}
void Kasumi::PlaneObject::INSPECT()
{
	ObjectMesh3D::INSPECT();
	ImGui::Text("init width: %f", _opt.width);
	ImGui::Text("init height: %f", _opt.height);
}
