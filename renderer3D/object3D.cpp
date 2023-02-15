#include "object3D.h"
unsigned int Kasumi::Object3D::ID_GLOBAL = 0;
void Kasumi::Object3D::INSPECT()
{
	_opt.pose.INSPECT();
}
void Kasumi::ObjectMesh3D::INSPECT()
{
	Object3D::INSPECT();

	if (_mesh == nullptr)
		return;

	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Vertices: %zu", _mesh->vertices().size());
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Indices: %zu", _mesh->indices().size());
}
void Kasumi::CubeObject::INSPECT()
{
	ObjectMesh3D::INSPECT();

	ImGui::Text("init width: %f", _opt.width);
	ImGui::Text("init height: %f", _opt.height);
	ImGui::Text("init depth: %f", _opt.depth);
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
