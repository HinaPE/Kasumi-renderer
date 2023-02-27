#include "object3D.h"
unsigned int Kasumi::Object3D::ID_GLOBAL = 0;
void Kasumi::Object3D::INSPECT()
{
	ImGui::Text("Transform");
	auto sliders = [&](const std::string &label, mVector3 &data, float sens)
	{
		if (ImGui::DragScalarN(label.c_str(), ImGuiDataType_Real, &data[0], 3, sens, &HinaPE::Constant::I_REAL_MIN, &HinaPE::Constant::I_REAL_MAX, "%.2f"))
			_opt.dirty = true;
	};
	sliders("Position", _opt.pose.position, 0.1f);
	sliders("Rotation", _opt.pose.euler, 0.1f);
	sliders("Scale", _opt.pose.scale, 0.031f);
}
void Kasumi::ObjectMesh3D::INSPECT()
{
	Object3D::INSPECT();

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
void Kasumi::ObjectMesh3D::_update_uniform()
{
	Renderable::_update_uniform();
	_shader->uniform("model", Object3D::_opt.pose.get_model_matrix());
	Shader::DefaultLineShader->uniform("model", Object3D::_opt.pose.get_model_matrix());
}
void Kasumi::ObjectMesh3D::_rebuild_()
{
	Object3D::_rebuild_();

	if (!_opt.dirty)
		return;

	if (!_opt.texture_path.empty())
		_mesh = std::make_shared<Mesh>(_opt.mesh_name, _opt.texture_path);
	else
		_mesh = std::make_shared<Mesh>(_opt.mesh_name, _opt.color);

	_opt.dirty = false;
}
void Kasumi::ObjectMesh3D::VALID_CHECK() const
{
	if (_mesh == nullptr)
		throw std::runtime_error("Mesh is nullptr");
}