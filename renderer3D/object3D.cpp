#include "object3D.h"
void Kasumi::Object::inspect()
{
	_pose.inspect();
}
void Kasumi::ObjectMesh3D::inspect()
{
	Object::inspect();

	if (_mesh == nullptr)
		return;

	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Vertices: %zu", _mesh->vertices().size());
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Indices: %zu", _mesh->indices().size());
}
