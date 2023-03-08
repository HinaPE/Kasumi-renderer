#include "GLFW/glfw3.h"
#include "scene.h"
#include "json/json11.hpp"

Kasumi::Scene3D::Scene3D()
{
	_scene_opt._ray = std::make_shared<ObjectLines3D>();
	_scene_opt._ray_hit = std::make_shared<ObjectPoints3D>();
	_particles = std::make_shared<ObjectParticles3D>();
	_grid = std::make_shared<ObjectGrid3D>();
//	read_scene();

	// debug point
	_scene_opt.debug_point_obj = std::make_shared<ObjectPoints3D>();
}
void Kasumi::Scene3D::add(const Kasumi::ObjectMesh3DPtr &object)
{
	_objects[object->ID] = object;
	_selected = static_cast<int>(object->ID);
}
void Kasumi::Scene3D::add(const ObjectParticles3DPtr &object)
{
	_particle_objects[object->ID] = object;
	_selected = static_cast<int>(object->ID);
}
void Kasumi::Scene3D::add(const Kasumi::ObjectLines3DInstancedPtr &object)
{
	_line_objects[object->ID] = object;
	_selected = static_cast<int>(object->ID);
}
void Kasumi::Scene3D::add(const Kasumi::ObjectPoints3DPtr &object)
{
	_point_objects[object->ID] = object;
	_selected = static_cast<int>(object->ID);
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
	for (auto &pair: _particle_objects)
		pair.second->render();
	for (auto &pair: _line_objects)
		pair.second->render();
	for (auto &pair: _point_objects)
		pair.second->render();

	if (_scene_opt._ray_enable)
	{
		_scene_opt._ray->render();
		_scene_opt._ray_hit->render();
	}

	if (_scene_opt._line_enable)
		ObjectLines3D::DefaultLines->render();

	if (_scene_opt._point_enable)
	{
		ObjectPoints3D::DefaultPoints->render();
		_scene_opt.debug_point_obj->clear();
		_scene_opt.debug_point_obj->add(_scene_opt.debug_point);
		_scene_opt.debug_point_obj->render();
	}

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
	if (key == GLFW_KEY_P && action == GLFW_PRESS) { _scene_opt._particle_mode = !_scene_opt._particle_mode; }
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
	if (!_scene_opt._particle_mode)
	{
		for (auto &o: _objects)
		{
			auto hit = o.second->ray_cast(ray);
			if (hit.is_intersecting && (!res.is_intersecting || hit.distance < res.distance))
				res = hit;
		}
	} else // TODO: error here, don't use
	{
		for (auto &o: _particle_objects)
		{
			auto hit = o.second->ray_cast(ray);
			if (hit.is_intersecting && (!res.is_intersecting || hit.distance < res.distance))
				res = hit;
		}
	}
	return res;
}

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
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		MOUSE_LEFT = true;
		auto x_pos = Platform::GetCursorPos().first;
		auto y_pos = Platform::GetCursorPos().second;

		real u_x = x_pos / Camera::MainCamera->_opt.width * 2 - 1;
		real u_y = 1 - y_pos / Camera::MainCamera->_opt.height * 2;
		auto ray = Camera::MainCamera->get_ray({u_x, u_y});
		auto res = ray_cast(ray);
		if (res.is_intersecting)
		{
			if (_scene_opt._particle_mode)
			{
				_particle_objects[res.ID]->_dirty = true;
				_particle_objects[res.ID]->_inst_id = static_cast<int>(res.particleID);
				_selected_particle = static_cast<int>(res.particleID);
			}
			_selected = static_cast<int>(res.ID);
		}
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		MOUSE_LEFT = false;
		FIRST_CLICK_LEFT = true;
	}
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS) { MOUSE_MID = true; }
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
	{
		MOUSE_MID = false;
		FIRST_CLICK_MID = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) { MOUSE_RIGHT = true; }
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{
		MOUSE_RIGHT = false;
		FIRST_CLICK_RIGHT = true;
	}
}
void Kasumi::Scene3D::mouse_scroll(double x_offset, double y_offset) { Kasumi::Camera::MainCamera->mouse_scroll(x_offset, y_offset); }
void Kasumi::Scene3D::mouse_cursor(double x_pos, double y_pos)
{
	Kasumi::Camera::MainCamera->mouse_cursor(x_pos, y_pos);
	if (MOUSE_LEFT)
	{
		real u_x = x_pos / Camera::MainCamera->_opt.width * 2 - 1;
		real u_y = 1 - y_pos / Camera::MainCamera->_opt.height * 2;
		auto ray = Camera::MainCamera->get_ray({u_x, u_y});
		auto res = ray_cast(ray);
		if (res.is_intersecting)
		{
			if (!FIRST_CLICK_LEFT)
			{
				if (_scene_opt._particle_mode)
				{
					auto delta = mVector2{u_x, u_y} - PRE_MOUSE_POS;
					auto particle = _particle_objects[res.ID]->_poses[res.particleID];
					particle.position += Camera::MainCamera->_right() * delta.x() * static_cast<real>(6.5);
					particle.position += Camera::MainCamera->_up() * delta.y() * static_cast<real>(6.5);
				} else
				{
					auto delta = mVector2{u_x, u_y} - PRE_MOUSE_POS;
					_objects[res.ID]->POSE.position += Camera::MainCamera->_right() * delta.x() * static_cast<real>(6.5);
					_objects[res.ID]->POSE.position += Camera::MainCamera->_up() * delta.y() * static_cast<real>(6.5);
					_objects[res.ID]->_dirty = true;
				}
			}
			PRE_MOUSE_POS = {u_x, u_y};
			FIRST_CLICK_LEFT = false;
			_selected = static_cast<int>(res.ID);
		}
	}
}

void Kasumi::Scene3D::INSPECT()
{
	ImGui::Text("Scene Info");
	ImGui::Text("Select Mode: %s", _scene_opt._particle_mode ? "Particle" : "Object");

	if (_objects.empty())
		return;

	for (auto &pair: _objects)
		ImGui::RadioButton((pair.second->NAME + ": " + std::to_string(pair.first)).c_str(), &_selected, static_cast<int>(pair.first));
	for (auto &pair: _particle_objects)
		ImGui::RadioButton((pair.second->NAME + ": " + std::to_string(pair.first)).c_str(), &_selected, static_cast<int>(pair.first));

	if (_objects.contains(_selected))
		_objects[_selected]->INSPECT();
	else if (_particle_objects.contains(_selected))
		_particle_objects[_selected]->INSPECT();

	ImGui::Separator();


	// Debug Info Area
//	ImGui::BulletText("Debug Info");
//	ImGui::DragScalarN("Debug Point", ImGuiDataType_Real, &_scene_opt.debug_point[0], 3, 0.1, &HinaPE::Constant::I_REAL_MIN, &HinaPE::Constant::I_REAL_MAX, "%.2f");
//	if (ImGui::Button("Show Closest Point"))
//	{
//		auto &o = _objects[_selected];
//		if (is<HinaPE::Geom::Surface3>(o.get()))
//		{
//			mVector3 p = as<HinaPE::Geom::Surface3>(o.get())->closest_point(_scene_opt.debug_point);
//			ObjectPoints3D::DefaultPoints->add(p);
//		}
//	}
//	ImGui::SameLine();
//	if (ImGui::Button("Clear"))
//	{
//		ObjectPoints3D::DefaultPoints->clear();
//	}
//	ImGui::Text("Inside: %s", _scene_opt.inside ? "true" : "false");
//	ImGui::SameLine();
//	if (ImGui::Button("Point inside"))
//	{
//		auto &o = _objects[_selected];
//		if (is<HinaPE::Geom::Surface3>(o.get()))
//			_scene_opt.inside = as<HinaPE::Geom::Surface3>(o.get())->is_inside(_scene_opt.debug_point);
//	}


	ImGui::Separator();
	if (_scene_opt._ray_enable)
	{
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
		pair.second->VALID_CHECK();
	for (auto &pair: _particle_objects)
		pair.second->VALID_CHECK();
}
