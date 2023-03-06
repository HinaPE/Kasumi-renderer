#include "object3D.h"
#include "igl/ray_mesh_intersect.h"

unsigned int Kasumi::IDBase::ID_GLOBAL = 0;
std::shared_ptr<Kasumi::ObjectLines3D> Kasumi::ObjectLines3D::DefaultLines = nullptr;
std::shared_ptr<Kasumi::ObjectPoints3D> Kasumi::ObjectPoints3D::DefaultPoints = nullptr;

// ==================== Object3D ====================
auto Kasumi::ObjectMesh3D::ray_cast(const mRay3 &ray) const -> HinaPE::Geom::SurfaceRayIntersection3
{
	HinaPE::Geom::SurfaceRayIntersection3 res;
	const auto &verts_local = _mesh->_verts_eigen4;
	const auto &idxs = _mesh->_idxs_eigen;
	auto model = POSE.get_model_matrix()._m;
	auto t = (model * verts_local.transpose());
	Eigen::MatrixXd verts_world = t.transpose();

	Eigen::MatrixXd verts_world_3 = verts_world.block(0, 0, verts_world.rows(), 3);

	std::vector<igl::Hit> hits;
	res.is_intersecting = igl::ray_mesh_intersect(ray._origin._v, ray._direction._v, verts_world_3, idxs, hits);
	for (auto const &hit: hits)
	{
		res.point = ray._origin + static_cast<real>(hit.t) * ray._direction;
		res.distance = (static_cast<real>(hit.t) * ray._direction).length();
		return res;
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
	_shader->uniform("model", POSE.get_model_matrix());
	Shader::DefaultLineShader->uniform("model", POSE.get_model_matrix());
}
void Kasumi::ObjectMesh3D::_init(const std::string &MESH, const std::string &TEXTURE, const mVector3 &COLOR)
{
	if (!TEXTURE.empty())
		_mesh = std::make_shared<Mesh>(MESH, TEXTURE);
	else
		_mesh = std::make_shared<Mesh>(MESH, COLOR);
}
void Kasumi::ObjectMesh3D::INSPECT()
{
	PoseBase::INSPECT();

	if (_mesh == nullptr)
		return;

	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Vertices: %zu", _mesh->vertices().size());
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh Indices: %zu", _mesh->indices().size());
}
void Kasumi::ObjectMesh3D::VALID_CHECK() const
{
	if (_mesh == nullptr)
		throw std::runtime_error("Mesh is nullptr");
	if (_surface == nullptr)
		throw std::runtime_error("Surface is nullptr");
}

// ==================== ObjectLines3D ====================
Kasumi::ObjectLines3D::ObjectLines3D()
{
	NAME = "Line";
	_shader = Shader::DefaultLineShader;
	_lines = std::make_shared<Lines>();
}
void Kasumi::ObjectLines3D::Init() { DefaultLines = std::make_shared<Kasumi::ObjectLines3D>(); }
void Kasumi::ObjectLines3D::add(const mVector3 &start, const mVector3 &end, const mVector3 &color) { _lines->add(start, end, color); }
void Kasumi::ObjectLines3D::clear() { _lines->clear(); }
void Kasumi::ObjectLines3D::_draw()
{
	if (_lines == nullptr) return;
	_lines->render(*_shader);
}
void Kasumi::ObjectLines3D::_update_uniform()
{
	Renderable::_update_uniform();
	_shader->uniform("model", POSE.get_model_matrix());
}

// ==================== ObjectPoints3D ====================
Kasumi::ObjectPoints3D::ObjectPoints3D()
{
	NAME = "Points";
	_shader = Shader::DefaultPointShader;
	_points = std::make_shared<Points>();
}
void Kasumi::ObjectPoints3D::Init() { DefaultPoints = std::make_shared<Kasumi::ObjectPoints3D>(); }
void Kasumi::ObjectPoints3D::add(const mVector3 &point, const mVector3 &color) { _points->add(point, color); }
void Kasumi::ObjectPoints3D::clear() { _points->clear(); }
void Kasumi::ObjectPoints3D::_draw()
{
	if (_points == nullptr) return;
	_points->render(*_shader);
}
void Kasumi::ObjectPoints3D::_update_uniform()
{
	Renderable::_update_uniform();
	_shader->uniform("model", POSE.get_model_matrix());
}
