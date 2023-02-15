#include "object3D.h"
static unsigned int ID_GLOBAL = 0;
Kasumi::Object3D::Object3D() : ID(ID_GLOBAL++) {}
void Kasumi::Object3D::_inspect()
{
	_pose._inspect();
}
void Kasumi::ObjectMesh3D::_inspect()
{
	Object3D::_inspect();

	if (_mesh == nullptr)
		return;

	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Vertices: %zu", _mesh->vertices().size());
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Indices: %zu", _mesh->indices().size());
}
void Kasumi::ObjectMesh3D::_draw()
{
	if (_mesh == nullptr)
		return;

	_mesh->render(*_shader);
}
