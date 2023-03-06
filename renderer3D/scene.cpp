#include "scene.h"

Kasumi::Scene3D::Scene3D()
{
	_ray = std::make_shared<LinesObject>();
	_ray_hit = std::make_shared<PointsObject>();
}
void Kasumi::Scene3D::add(const Kasumi::Object3DPtr &object)
{
	_objects[object->ID] = object;
	selected = static_cast<int>(object->ID);
}
void Kasumi::Scene3D::remove(unsigned int id)
{
	auto it = _objects.find(id);
	if (it != _objects.end())
		_objects.erase(it);
}
void Kasumi::Scene3D::draw()
{
	for (auto &pair: _objects)
		if (is_renderable(pair.second.get()))
			as_renderable(pair.second.get())->render();

	if (_ray_enable)
	{
		_ray->render();
		_ray_hit->render();
	}

	if (_line_enable)
		Kasumi::LinesObject::DefaultLines->render();

	if (_point_enable)
		Kasumi::PointsObject::DefaultPoints->render();
}
void Kasumi::Scene3D::key(int key, int scancode, int action, int mods)
{
	Kasumi::Camera::MainCamera->key(key, scancode, action, mods);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		for (auto &pair: _objects)
			if (dynamic_cast<const ObjectMesh3D *>(pair.second.get()))
				dynamic_cast<const ObjectMesh3D *>(pair.second.get())->_switch_wireframe();
			else if (dynamic_cast<const ParticlesObject *>(pair.second.get()))
				dynamic_cast<const ParticlesObject *>(pair.second.get())->_switch_wireframe();
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		for (auto &pair: _objects)
			if (dynamic_cast<const ObjectMesh3D *>(pair.second.get()))
				dynamic_cast<const ObjectMesh3D *>(pair.second.get())->_switch_bbox();
			else if (dynamic_cast<const ParticlesObject *>(pair.second.get()))
				dynamic_cast<const ParticlesObject *>(pair.second.get())->_switch_bbox();
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		for (auto &pair: _objects)
			if (dynamic_cast<const ObjectMesh3D *>(pair.second.get()))
				dynamic_cast<const ObjectMesh3D *>(pair.second.get())->_switch_surface();
			else if (dynamic_cast<const ParticlesObject *>(pair.second.get()))
				dynamic_cast<const ParticlesObject *>(pair.second.get())->_switch_surface();
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		_ray_enable = true;
		auto ray = Kasumi::Camera::MainCamera->get_ray(mVector2::Zero());
		_ray_hit_info = ray_cast(ray);
		if (_ray_hit_info.is_intersecting)
		{
			_ray->add(Kasumi::Camera::MainCamera->_opt.position, _ray_hit_info.point);
			_ray_hit->add(_ray_hit_info.point);
		}
	}
	if (key == GLFW_KEY_R && action == GLFW_RELEASE)
	{
		_ray_enable = false;
		_ray->clear();
		_ray_hit->clear();
	}
}

void Kasumi::Scene3D::INSPECT()
{
	ImGui::Text("Scene Info");

	if (_objects.empty())
		return;

	for (auto &pair: _objects)
	{
		ImGui::RadioButton((pair.second->NAME + ": " + std::to_string(pair.first)).c_str(), &selected, static_cast<int>(pair.first));
	}
	if (!_objects.contains(selected))
		selected = static_cast<int>(_objects.rbegin()->first);
	_objects[selected]->INSPECT();

	if (_ray_enable)
	{
		ImGui::Separator();
		ImGui::Text("Ray Hit: %s", _ray_hit_info.is_intersecting ? "true" : "false");
		if (_ray_hit_info.is_intersecting)
		{
			ImGui::Text("Ray Hit Point: (%.3f, %.3f, %.3f)", _ray_hit_info.point.x(), _ray_hit_info.point.y(), _ray_hit_info.point.z());
			ImGui::Text("Ray Hit Normal: (%.3f, %.3f, %.3f)", _ray_hit_info.normal.x(), _ray_hit_info.normal.y(), _ray_hit_info.normal.z());
			ImGui::Text("Ray Hit Distance: %.3f", _ray_hit_info.distance);
		}
	}
}
void Kasumi::Scene3D::VALID_CHECK() const
{
	for (auto &pair: _objects)
		if (need_valid_check(pair.second.get()))
			as_valid_check(pair.second.get())->VALID_CHECK();
}
auto Kasumi::Scene3D::ray_cast(const mRay3 &ray) -> HinaPE::Geom::SurfaceRayIntersection3
{
	HinaPE::Geom::SurfaceRayIntersection3 res;
	for (auto &o: _objects)
	{
		if (is<ObjectMesh3D>(o.second.get()))
		{
			auto mesh_obj = as<ObjectMesh3D>(o.second.get());
			auto hit = mesh_obj->ray_cast(ray);
			if (hit.is_intersecting && (!res.is_intersecting || hit.distance < res.distance))
				res = hit;
		}
	}
	return res;
}

// @formatter:off
void Kasumi::Scene3D::mouse_button(int button, int action, int mods) { Kasumi::Camera::MainCamera->mouse_button(button, action, mods); }
void Kasumi::Scene3D::mouse_scroll(double x_offset, double y_offset) { Kasumi::Camera::MainCamera->mouse_scroll(x_offset, y_offset); }
void Kasumi::Scene3D::mouse_cursor(double x_pos, double y_pos) { Kasumi::Camera::MainCamera->mouse_cursor(x_pos, y_pos); }
// @formatter:on
