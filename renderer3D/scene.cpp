#include "scene.h"

void Kasumi::Scene3D::add(const Kasumi::Object3DPtr &object) { _objects[object->ID] = object; }
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
}
void Kasumi::Scene3D::key(int key, int scancode, int action, int mods)
{
	Kasumi::Camera::MainCamera->key(key, scancode, action, mods);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		for (auto &pair: _objects)
			if (dynamic_cast<const ObjectMesh3D *>(pair.second.get()))
				dynamic_cast<const ObjectMesh3D *>(pair.second.get())->switch_wireframe();
			else if (dynamic_cast<const ParticlesObject *>(pair.second.get()))
				dynamic_cast<const ParticlesObject *>(pair.second.get())->switch_wireframe();
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		for (auto &pair: _objects)
			if (dynamic_cast<const ObjectMesh3D *>(pair.second.get()))
				dynamic_cast<const ObjectMesh3D *>(pair.second.get())->switch_bbox();
			else if (dynamic_cast<const ParticlesObject *>(pair.second.get()))
				dynamic_cast<const ParticlesObject *>(pair.second.get())->switch_bbox();
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		for (auto &pair: _objects)
			if (dynamic_cast<const ObjectMesh3D *>(pair.second.get()))
				dynamic_cast<const ObjectMesh3D *>(pair.second.get())->switch_surface();
			else if (dynamic_cast<const ParticlesObject *>(pair.second.get()))
				dynamic_cast<const ParticlesObject *>(pair.second.get())->switch_surface();
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
	auto &obj = _objects[selected];
	obj->INSPECT();
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
void Kasumi::Scene3D::mouse_button(int button, int action, int mods) { Kasumi::Camera::MainCamera->mouse_button(button, action, mods); ray_cast(mRay3()); }
void Kasumi::Scene3D::mouse_scroll(double x_offset, double y_offset) { Kasumi::Camera::MainCamera->mouse_scroll(x_offset, y_offset); }
void Kasumi::Scene3D::mouse_cursor(double x_pos, double y_pos) { Kasumi::Camera::MainCamera->mouse_cursor(x_pos, y_pos); }
// @formatter:on