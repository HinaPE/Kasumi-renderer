#include "scene.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

Kasumi::Scene::Scene() = default;
Kasumi::Scene::~Scene() { clear(); }

// ================================================== Public Methods ==================================================

auto Kasumi::Scene::read_scene(const std::string &path) -> std::string
{
	std::ifstream infile(path);
	if (!infile.is_open())
		return "PATH NOT VALID";
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
			std::string shader_name;
			mVector3 position, rotation, scale = mVector3(1, 1, 1);
			std::string attrib;

			unsigned int obj_id = std::numeric_limits<unsigned int>::max();
			while (iss >> attrib)
			{
				if (attrib == "path")
				{
					iss >> model_path;
					obj_id = add_object(std::make_shared<Model>(model_path));
				} else if (attrib == "Hatsune_Miku_V4X")
					obj_id = add_object(std::make_shared<Model>(std::string(ModelDir) + "Hatsune_Miku_V4X/Hatsune_Miku_V4X.pmx"));
				else if (attrib == "cube" || attrib == "sphere" || attrib == "cylinder")
				{
					std::string color;
					iss >> color;
					obj_id = add_object(std::make_shared<Model>(attrib, color));
				} else if (attrib == "shader")
					iss >> shader_name;
				else if (attrib == "position")
					iss >> position.x >> position.y >> position.z;
				else if (attrib == "rotation")
					iss >> rotation.x >> rotation.y >> rotation.z;
				else if (attrib == "scale")
					iss >> scale.x >> scale.y >> scale.z;
			}
			if (obj_id == std::numeric_limits<unsigned int>::max())
				continue;
			set_position(obj_id, position);
			set_rotation(obj_id, rotation);
			set_scale(obj_id, scale);
		} else if (type == "shader")
		{
			std::string vertex_shader, fragment_shader, geometry_shader;
			if (!(iss >> vertex_shader >> fragment_shader))
				continue;
			// TODO:
		} else
		{
			error_message += "UNKNOWN TYPE: " + type;
		}
	}
	return error_message;
}

auto Kasumi::Scene::write_to_file(const std::string &path) -> std::string
{
	// TODO: TOO COMPLICATED, NOT COMPLETED
	std::string error_message;

	aiScene scene;
	{
		scene.mRootNode = new aiNode();
	}
	{ // Scene Objects
		for (auto &entry: _scene_objects)
		{
			auto &object = entry.second;
		}
	}
	return error_message;
}

auto Kasumi::Scene::add_object(Kasumi::ModelPtr &&o) -> unsigned int
{
	static unsigned static_obj_id = 0;
	int id = static_obj_id++;
	_scene_objects[id] = std::make_shared<SceneObject>(std::move(o));
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
		obj.second->render();
	}
}

// ================================================== Public Methods ==================================================


// ================================================== Private Methods ==================================================

void Kasumi::Scene::key(int key, int scancode, int action, int mods) { _scene_camera->key(key, scancode, action, mods); }
void Kasumi::Scene::mouse_button(int button, int action, int mods) { _scene_camera->mouse_button(button, action, mods); }
void Kasumi::Scene::mouse_scroll(double x_offset, double y_offset) { _scene_camera->mouse_scroll(x_offset, y_offset); }
void Kasumi::Scene::mouse_cursor(double x_pos, double y_pos) { _scene_camera->mouse_cursor(x_pos, y_pos); }
void Kasumi::Scene::ui_sidebar()
{
	auto selected_object = get_object(_state.selected_object_id);
	if (selected_object == nullptr)
		return;

	auto sliders = [&](std::string label, mVector3 &data, float sens)
	{
		label += "##" + std::to_string(_state.selected_object_id);
		ImGui::DragFloat3(label.c_str(), &data[0], sens);
	};
	ImGui::Text("Edit Pose");
	sliders("Position", selected_object->_pose.position, 0.1f);
	sliders("Rotation", selected_object->_pose.euler, 0.1f);
	sliders("Scale", selected_object->_pose.scale, 0.031f);
	ImGui::Checkbox("Wireframe", &selected_object->get_model()->_opt.render_wireframe);
	ImGui::Separator();
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
}

// ================================================== Private Methods ==================================================