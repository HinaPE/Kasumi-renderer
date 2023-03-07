#include "GLFW/glfw3.h"
#include "scene.h"
#include "json/json11.hpp"

Kasumi::Scene3D::Scene3D()
{
	_scene_opt._ray = std::make_shared<ObjectLines3D>();
	_scene_opt._ray_hit = std::make_shared<ObjectPoints3D>();
	_particles = std::make_shared<ObjectParticles3D>();
	_grid = std::make_shared<ObjectGrid3D>();
	read_scene();
}
void Kasumi::Scene3D::add(const Kasumi::ObjectMesh3DPtr &object)
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
		pair.second->render();

	if (_scene_opt._ray_enable)
	{
		_scene_opt._ray->render();
		_scene_opt._ray_hit->render();
	}

	if (_scene_opt._line_enable)
		ObjectLines3D::DefaultLines->render();

	if (_scene_opt._point_enable)
		ObjectPoints3D::DefaultPoints->render();

//	_particles->render();
//	_grid->render();
}
void Kasumi::Scene3D::read_scene(const std::string &path)
{
	std::stringstream ss;
	{
		std::ifstream file(path);
		ss << file.rdbuf();
		file.close();
	}
	std::string src = ss.str();
	std::string err;
	auto scene = json11::Json::parse(src, err, json11::JsonParse::STANDARD);
	scene.type();
}
void Kasumi::Scene3D::export_scene(const std::string &path)
{
}
void Kasumi::Scene3D::key(int key, int scancode, int action, int mods)
{
	Kasumi::Camera::MainCamera->key(key, scancode, action, mods);
	if (key == GLFW_KEY_W && action == GLFW_PRESS) { for (auto &pair: _objects) pair.second->_switch_wireframe(); }
	if (key == GLFW_KEY_B && action == GLFW_PRESS) { for (auto &pair: _objects) pair.second->_switch_bbox(); }
	if (key == GLFW_KEY_S && action == GLFW_PRESS) { for (auto &pair: _objects) pair.second->_switch_surface(); }
	if (key == GLFW_KEY_R && action == GLFW_PRESS)
	{
		_scene_opt._ray_enable = true;
		auto ray = Kasumi::Camera::MainCamera->get_ray(mVector2::Zero());
		_scene_opt._ray_hit_info = ray_cast(ray);
		if (_scene_opt._ray_hit_info.is_intersecting)
		{
			_scene_opt._ray->add(Kasumi::Camera::MainCamera->_opt.position, _scene_opt._ray_hit_info.point);
			_scene_opt._ray_hit->add(_scene_opt._ray_hit_info.point);
		}
	}
	if (key == GLFW_KEY_R && action == GLFW_RELEASE)
	{
		_scene_opt._ray_enable = false;
		_scene_opt._ray->clear();
		_scene_opt._ray_hit->clear();
	}
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
static bool MOUSE_LEFT = false;
static bool MOUSE_MID = false;
static bool MOUSE_RIGHT = false;
static bool FIRST_CLICK_LEFT = true;
static bool FIRST_CLICK_MID = true;
static bool FIRST_CLICK_RIGHT = true;
static mVector2 PRE_MOUSE_POS = mVector2::Zero();
void Kasumi::Scene3D::mouse_button(int button, int action, int mods)
{
	Kasumi::Camera::MainCamera->mouse_button(button, action, mods);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) { MOUSE_LEFT = true; }
 	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) { MOUSE_LEFT = false; FIRST_CLICK_LEFT = true; }
 	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) { MOUSE_MID = true; }
 	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE) { MOUSE_MID = false; FIRST_CLICK_MID = true; }
 	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) { MOUSE_RIGHT = true; }
 	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) { MOUSE_RIGHT = false; FIRST_CLICK_RIGHT = true; }
}
void Kasumi::Scene3D::mouse_scroll(double x_offset, double y_offset) { Kasumi::Camera::MainCamera->mouse_scroll(x_offset, y_offset); }
void Kasumi::Scene3D::mouse_cursor(double x_pos, double y_pos)
{
	Kasumi::Camera::MainCamera->mouse_cursor(x_pos, y_pos);
	if (MOUSE_LEFT)
	{
		real u_x = x_pos / 1024.0 * 2 - 1;
		real u_y = 1 - y_pos / 768.0 * 2;
		auto ray = Camera::MainCamera->get_ray({u_x, u_y});
		auto res = ray_cast(ray);
		if (res.is_intersecting)
		{
			if (!FIRST_CLICK_LEFT)
			{
				auto delta = mVector2{u_x, u_y} - PRE_MOUSE_POS;
				_objects[res.ID]->POSE.position += Camera::MainCamera->_right() * delta.x() * static_cast<real>(6.5);
				_objects[res.ID]->POSE.position += Camera::MainCamera->_up() * delta.y() * static_cast<real>(6.5);
			}
			PRE_MOUSE_POS = {u_x, u_y};
			FIRST_CLICK_LEFT = false;
			selected = static_cast<int>(res.ID);
		}
	}
}
// @formatter:on

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

	if (_scene_opt._ray_enable)
	{
		ImGui::Separator();
		ImGui::Text("Ray Hit: %s", _scene_opt._ray_hit_info.is_intersecting ? "true" : "false");
		if (_scene_opt._ray_hit_info.is_intersecting)
		{
			ImGui::Text("Ray Hit Point: (%.3f, %.3f, %.3f)", _scene_opt._ray_hit_info.point.x(), _scene_opt._ray_hit_info.point.y(), _scene_opt._ray_hit_info.point.z());
			ImGui::Text("Ray Hit Normal: (%.3f, %.3f, %.3f)", _scene_opt._ray_hit_info.normal.x(), _scene_opt._ray_hit_info.normal.y(), _scene_opt._ray_hit_info.normal.z());
			ImGui::Text("Ray Hit Distance: %.3f", _scene_opt._ray_hit_info.distance);
		}
	}
}
void Kasumi::Scene3D::VALID_CHECK() const
{
	for (auto &pair: _objects)
		if (need_valid_check(pair.second.get()))
			as_valid_check(pair.second.get())->VALID_CHECK();
}
