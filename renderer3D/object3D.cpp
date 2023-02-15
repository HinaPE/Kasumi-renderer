#include "object3D.h"
unsigned int Kasumi::Object3D::ID_GLOBAL = 0;
void Kasumi::Object3D::_inspect()
{
	_opt.pose._inspect();
}
void Kasumi::ObjectMesh3D::_inspect()
{
	Object3D::_inspect();

	if (_mesh == nullptr)
		return;

	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Vertices: %zu", _mesh->vertices().size());
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Indices: %zu", _mesh->indices().size());
}
void Kasumi::CubeObject::_inspect()
{
	ObjectMesh3D::_inspect();

	ImGui::Text("width: %f", _opt.width);
	ImGui::Text("height: %f", _opt.height);
	ImGui::Text("depth: %f", _opt.depth);
}
void Kasumi::ObjectMesh3D::_draw()
{
	if (_mesh == nullptr)
		return;

	_mesh->render(*_shader);
}
void Kasumi::ObjectMesh3D::VALID_CHECK() const
{
	if (_mesh == nullptr)
		throw std::runtime_error("Mesh is nullptr");
}
