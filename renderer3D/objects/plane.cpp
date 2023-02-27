#include "plane.h"

void Kasumi::PlaneObject::INSPECT()
{
	ObjectMesh3D::INSPECT();
	ImGui::Text("init width: %f", _opt.width);
	ImGui::Text("init height: %f", _opt.height);
}

void Kasumi::PlaneObject::_rebuild_()
{
	ObjectMesh3D::_rebuild_();
}
