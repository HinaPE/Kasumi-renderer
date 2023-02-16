#include "object3D.h"
unsigned int Kasumi::Object3D::ID_GLOBAL = 0;
void Kasumi::Object3D::INSPECT()
{
	ImGui::Text("Transform");
	auto sliders = [&](const std::string &label, mVector3 &data, float sens)
	{
#if HINAPE_DOUBLE
		auto data_float = data.as_float();
		ImGui::DragFloat3(label.c_str(), &data_float[0], sens);
		data = data_float.as_double();
#else
		ImGui::DragFloat3(label.c_str(), &data[0], sens);
#endif
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
}
void Kasumi::ObjectMesh3D::sync_opt()
{
	if (!Object3D::_opt.dirty)
		return;

	if (!_opt.texture_path.empty())
		_mesh = std::make_shared<Mesh>(_opt.mesh_name, _opt.texture_path);
	else
		_mesh = std::make_shared<Mesh>(_opt.mesh_name, _opt.color);

	Object3D::sync_opt();
}
void Kasumi::ObjectMesh3D::VALID_CHECK() const
{
	if (_mesh == nullptr)
		throw std::runtime_error("Mesh is nullptr");
}