#include "plane.h"

Kasumi::PlaneObject::PlaneObject()
{
	NAME = "Plane" + std::to_string(ID);
	MESH = "plane";
	_shader = Shader::DefaultMeshShader;
	init();
}
void Kasumi::PlaneObject::INSPECT()
{
	ObjectMesh3D::INSPECT();
	ImGui::Text("init width: %f", _opt.width);
	ImGui::Text("init height: %f", _opt.height);
}
