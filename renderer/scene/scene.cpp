#include "scene.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

Kasumi::Scene::Scene()
{
	// create a default camera
	Camera::Opt camera_opt;
	camera_opt.aspect_ratio = 1500.f / 700.f;
	_scene_camera = std::make_shared<Camera>(camera_opt);

	// create a default light
	Light::Opt light_opt;
	_scene_light = std::make_shared<Light>(light_opt);
}
Kasumi::Scene::~Scene() { clear(); }

// ================================================== Public Methods ==================================================

void Kasumi::Scene::read_scene(const std::string &path)
{
	std::ifstream infile(path);
	if (!infile.is_open())
		throw std::runtime_error("Failed to open scene file: " + path);
	std::string error_message;
	std::string line;
	while (std::getline(infile, line))
	{
		if (line.empty())
			continue;
		std::istringstream iss(line);
		std::string type;
		if (!(iss >> type))
			continue;
		if (type == "model")
		{
			std::string model_path;
			mVector3 position, rotation, scale = mVector3(1, 1, 1);

			unsigned int obj_id = std::numeric_limits<unsigned int>::max();
			std::string attrib;
			while (iss >> attrib)
			{
				if (attrib == "path")
				{
					iss >> model_path;
					obj_id = add_object(std::make_shared<Model>(model_path));
				} else if (attrib == "Hatsune_Miku_V4X")
				{
					obj_id = add_object(std::make_shared<Model>(std::string(ModelDir) + "Hatsune_Miku_V4X/Hatsune_Miku_V4X.pmx"));
					get_object(obj_id)->_name = "Hatsune Miku V4X";
				} else if (attrib == "desk")
				{
					obj_id = add_object(std::make_shared<Model>(std::string(ModelDir) + "desk.obj"));
					get_object(obj_id)->_name = "desk";
				} else if (attrib == "background")
				{
					obj_id = add_object(std::make_shared<Model>(std::string(ModelDir) + "background.obj"));
					get_object(obj_id)->_name = "background";
				} else if (attrib == "cube" || attrib == "sphere" || attrib == "cylinder")
				{
					std::string color;
					iss >> color;
					std::transform(color.begin(), color.end(), color.begin(), [](unsigned char c) { return std::toupper(c); });
					if (color == "MIKU")
						obj_id = add_object(std::make_shared<Model>(attrib, HinaPE::Color::MIKU));
					else if (color == "RED")
						obj_id = add_object(std::make_shared<Model>(attrib, HinaPE::Color::RED));
					else if (color == "GREEN")
						obj_id = add_object(std::make_shared<Model>(attrib, HinaPE::Color::GREEN));
					else if (color == "BLUE")
						obj_id = add_object(std::make_shared<Model>(attrib, HinaPE::Color::BLUE));
					else if (color == "YELLOW")
						obj_id = add_object(std::make_shared<Model>(attrib, HinaPE::Color::YELLOW));
					else if (color == "PURPLE")
						obj_id = add_object(std::make_shared<Model>(attrib, HinaPE::Color::PURPLE));
					else if (color == "CYAN")
						obj_id = add_object(std::make_shared<Model>(attrib, HinaPE::Color::CYAN));
					else if (color == "WHITE")
						obj_id = add_object(std::make_shared<Model>(attrib, HinaPE::Color::WHITE));
					else if (color == "BLACK")
						obj_id = add_object(std::make_shared<Model>(attrib, HinaPE::Color::BLACK));
					else // is texture
						obj_id = add_object(std::make_shared<Model>(attrib, color));
					get_object(obj_id)->_name = attrib;
				} else if (attrib == "position")
					iss >> position.x() >> position.y() >> position.z();
				else if (attrib == "rotation")
					iss >> rotation.x() >> rotation.y() >> rotation.z();
				else if (attrib == "scale")
					iss >> scale.x() >> scale.y() >> scale.z();
			}
			if (obj_id == std::numeric_limits<unsigned int>::max())
				continue;
			get_object(obj_id)->position() = position;
			get_object(obj_id)->rotation() = rotation;
			get_object(obj_id)->scale() = scale;
		} else
			throw std::runtime_error("PARSE Type: " + type + " FAILED!");
	}
}

void Kasumi::Scene::write_to_file(const std::string &path)
{
	// TODO: TOO COMPLICATED, NOT COMPLETED YET
}

static unsigned static_obj_id = 0;

auto Kasumi::Scene::add_object(Kasumi::ModelPtr &o) -> unsigned int
{
	unsigned id = static_obj_id++;
	_scene_objects[id] = std::make_shared<SceneObject>(o);

	if (_state.selected_object_id == std::numeric_limits<unsigned int>::max())
		_state.selected_object_id = id;
	return id;
}

auto Kasumi::Scene::add_object(Kasumi::ModelPtr &&o) -> unsigned int
{
	unsigned id = static_obj_id++;
	_scene_objects[id] = std::make_shared<SceneObject>(std::move(o));

	if (_state.selected_object_id == std::numeric_limits<unsigned int>::max())
		_state.selected_object_id = id;
	return id;
}

void Kasumi::Scene::erase_object(unsigned int id)
{
	if (_scene_objects_erased.find(id) != _scene_objects_erased.end())
		return;
	_scene_objects_erased.insert({id, std::move(_scene_objects[id])});
	_scene_objects.erase(id);
}

void Kasumi::Scene::restore_object(unsigned int id)
{
	if (_scene_objects.find(id) != _scene_objects.end())
		return;
	_scene_objects.insert({id, std::move(_scene_objects[id])});
	_scene_objects_erased.erase(id);
}

void Kasumi::Scene::render()
{
	for (auto &obj: _scene_objects)
	{
		auto camera = get_camera();
		obj.second->update_mvp(camera->get_view(), camera->get_projection());
		_scene_light->update(_scene_camera);
		obj.second->update_light(_scene_light);
		obj.second->render();
	}
}

// ================================================== Public Methods ==================================================


// ================================================== Private Methods ==================================================

void Kasumi::Scene::key(int key, int scancode, int action, int mods)
{
	_scene_camera->key(key, scancode, action, mods);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		for (auto &obj: _scene_objects)
			obj.second->get_model()->_opt.render_wireframe = !obj.second->get_model()->_opt.render_wireframe;
}
void Kasumi::Scene::mouse_button(int button, int action, int mods) { _scene_camera->mouse_button(button, action, mods); }
void Kasumi::Scene::mouse_scroll(double x_offset, double y_offset) { _scene_camera->mouse_scroll(x_offset, y_offset); }
void Kasumi::Scene::mouse_cursor(double x_pos, double y_pos) { _scene_camera->mouse_cursor(x_pos, y_pos); }
void Kasumi::Scene::ui_sidebar()
{
	if (_state.selected_object_id == std::numeric_limits<unsigned int>::max())
		return;

	ImGui::Text("Selected Object");
	auto selected_object = get_object(_state.selected_object_id);
	static int selected_id = _state.selected_object_id;
	for (auto &obj: _scene_objects)
	{
		auto n = ("id: " + std::to_string(obj.first) + " " + obj.second->_name);
		ImGui::RadioButton(n.c_str(), &selected_id, obj.first);
	}
	_state.selected_object_id = selected_id;

	auto sliders = [&](std::string label, mVector3 &data, float sens)
	{
		label += "##" + std::to_string(_state.selected_object_id);
		ImGui::DragFloat3(label.c_str(), &data[0], sens);
	};
	ImGui::Text("Edit Pose");
	sliders("Position", selected_object->_pose.position, 0.1f);
	sliders("Rotation", selected_object->_pose.euler, 0.1f);
	sliders("Scale", selected_object->_pose.scale, 0.031f);
	ImGui::BeginDisabled(true);
	ImGui::Checkbox("Wireframe", &selected_object->get_model()->_opt.render_wireframe);
	ImGui::EndDisabled();
}

void Kasumi::Scene::for_each_item(const std::function<void(SceneObjectPtr &)> &func)
{
	for (auto &obj: _scene_objects)
		func(obj.second);
}

void Kasumi::Scene::clear()
{
	_scene_objects.clear();
	_scene_objects_erased.clear();

	_state.selected_camera_id = std::numeric_limits<unsigned int>::max();
	_state.selected_object_id = std::numeric_limits<unsigned int>::max();

	static_obj_id = 0;
}

// ================================================== Private Methods ==================================================