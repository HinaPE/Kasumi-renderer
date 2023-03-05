#include "object3D.h"
#include "igl/ray_mesh_intersect.h"

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
	const auto &verts_local = _mesh->_verts_eigen4;
	const auto &idxs = _mesh->_idxs_eigen;
	auto model = _pose.get_model_matrix()._m;
	auto t = (model * verts_local.transpose());
	Eigen::MatrixXd verts_world = t.transpose();

	Eigen::MatrixXd verts_world_3 = verts_world.block(0, 0, verts_world.rows(), 3);

	std::vector<igl::Hit> hits;
	bool is = igl::ray_mesh_intersect(ray._origin._v, ray._direction._v, verts_world_3, idxs, hits);
	for (auto const &hit: hits)
	{
		std::cout << hit.t << std::endl;
	}
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
