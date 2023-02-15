#include "cube.h"

void Kasumi::CubeObject::INSPECT()
{
	ObjectMesh3D::INSPECT();

	ImGui::Text("init width: %f", _opt.width);
	ImGui::Text("init height: %f", _opt.height);
	ImGui::Text("init depth: %f", _opt.depth);
}