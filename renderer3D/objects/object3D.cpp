#include "object3D.h"
unsigned int Kasumi::Object3D::ID_GLOBAL = 0;
void Kasumi::Object3D::INSPECT()
{
	ImGui::Text("Transform");
	auto sliders = [&](const std::string &label, mVector3 &data, float sens)
	{
		if (ImGui::DragScalarN(label.c_str(), ImGuiDataType_Real, &data[0], 3, sens, &HinaPE::Constant::I_REAL_MIN, &HinaPE::Constant::I_REAL_MAX, "%.2f"))
			_dirty = true;
	};
	sliders("Position", _pose.position, 0.1f);
	sliders("Rotation", _pose.euler, 0.1f);
	sliders("Scale", _pose.scale, 0.031f);
}
void Kasumi::ObjectMesh3D::INSPECT()
{
	Object3D::INSPECT();

	if (_mesh == nullptr)
		return;

	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Vertices: %zu", _mesh->vertices().size());
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Indices: %zu", _mesh->indices().size());
}
auto Kasumi::ObjectMesh3D::ray_cast(const mRay3 &ray) const -> HinaPE::Geom::SurfaceRayIntersection3
{
	HinaPE::Geom::SurfaceRayIntersection3 res;
	auto pos = _mesh->asEigenMatrixXMap();
	return res;
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
	_shader->uniform("model", _pose.get_model_matrix());
	Shader::DefaultLineShader->uniform("model", _pose.get_model_matrix());
}
void Kasumi::ObjectMesh3D::VALID_CHECK() const
{
	if (_mesh == nullptr)
		throw std::runtime_error("Mesh is nullptr");
}
void Kasumi::ObjectMesh3D::init()
{
	if (!TEXTURE.empty())
		_mesh = std::make_shared<Mesh>(MESH, TEXTURE);
	else
		_mesh = std::make_shared<Mesh>(MESH, COLOR);
}
