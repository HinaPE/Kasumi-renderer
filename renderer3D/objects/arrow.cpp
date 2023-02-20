#include "arrow.h"

void Kasumi::ArrowObject::INSPECT()
{
	ObjectMesh3D::INSPECT();

	ImGui::Text("init origin: %f %f %f", _opt.origin.x(), _opt.origin.y(), _opt.origin.z());
	ImGui::Text("init direction: %f %f %f", _opt.direction.x(), _opt.direction.y(), _opt.direction.z());
}