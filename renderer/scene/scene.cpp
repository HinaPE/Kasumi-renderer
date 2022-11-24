#include "scene.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "GLFW/glfw3.h"
#include "imgui.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

static unsigned static_obj_id = 0;
static unsigned static_shader_id = 0;
static unsigned static_camera_id = 0;

Kasumi::Scene::Scene()
{
    _opt.default_texture_shader_id = add_shader(std::string(ShaderDir) + "texture_shader_vertex.glsl", std::string(ShaderDir) + "texture_shader_fragment.glsl");
    _opt.default_color_shader_id = add_shader(std::string(ShaderDir) + "color_shader_vertex.glsl", std::string(ShaderDir) + "color_shader_fragment.glsl");
    _opt.default_camera_id = add_camera(); // default camera
    _opt.camera_dirty = true;
    _opt.shader_dirty = true;
    update();
}

Kasumi::Scene::~Scene()
{
    _scene_objects.clear();
    _scene_objects_erased.clear();
    _scene_cameras.clear();
    _scene_shaders.clear();

    _opt.default_camera_id = std::numeric_limits<unsigned int>::max();
    _opt.current_object_id = std::numeric_limits<unsigned int>::max();

    static_obj_id = 0;
    static_shader_id = 0;
    static_camera_id = 0;
}

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
                    obj_id = add_model(model_path).first;
                } else if (attrib == "Hatsune_Miku_V4X")
                    obj_id = add_model(std::string(ModelDir) + "Hatsune_Miku_V4X/Hatsune_Miku_V4X.pmx").first;
                else if (attrib == "cube" || attrib == "sphere" || attrib == "cylinder")
                {
                    std::string color;
                    iss >> color;
                    obj_id = add_primitive(attrib, color).first;
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
            if (iss >> geometry_shader)
                add_shader(vertex_shader, fragment_shader, geometry_shader);
            else
                add_shader(vertex_shader, fragment_shader);
        } else if (type == "camera")
        {
            add_camera();
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

auto Kasumi::Scene::add_model(const std::string &model_path, unsigned int shader_id) -> std::pair<unsigned int, ModelPtr>
{
    std::shared_ptr<Shader> shader = nullptr;
    if (shader_id != 0)
        shader = _scene_shaders.find(shader_id)->second;
    else
        shader = get_current_texture_shader();
    unsigned int id = static_obj_id++;
    auto model = std::make_shared<Model>(model_path, shader);
    auto res = _scene_objects.emplace(id, std::make_shared<SceneObject>(model));
    res.first->second->_id = id;
    res.first->second->use_shader(shader);
    _opt.current_object_id = id;
    _opt.object_dirty = true;
    return {id, model};
}

auto Kasumi::Scene::add_primitive(const std::string &primitive_name, const std::string &color) -> std::pair<unsigned int, ColoredMeshPtr>
{
    auto shader = get_current_color_shader();
    unsigned int id = static_obj_id++;
    auto mesh = std::make_shared<ColoredMesh>(primitive_name, color);
    auto res = _scene_objects.emplace(id, std::make_shared<SceneObject>(mesh));
    res.first->second->_id = id;
    res.first->second->use_shader(shader);
    _opt.current_object_id = id;
    _opt.object_dirty = true;
    return {id, mesh};
}

auto Kasumi::Scene::add_primitive(std::vector<ColoredMesh::Vertex> &&vertices, std::vector<ColoredMesh::Index> &&indices, const std::string &color) -> std::pair<unsigned int, ColoredMeshPtr>
{
    auto shader = get_current_color_shader();
    unsigned int id = static_obj_id++;
    auto mesh = std::make_shared<ColoredMesh>(std::move(vertices), std::move(indices), color);
    auto res = _scene_objects.emplace(id, std::make_shared<SceneObject>(mesh));
    res.first->second->_id = id;
    res.first->second->use_shader(shader);
    _opt.current_object_id = id;
    _opt.object_dirty = true;
    return {id, mesh};
}

auto Kasumi::Scene::add_primitive(std::vector<TexturedMesh::Vertex> &&vertices, std::vector<TexturedMesh::Index> &&indices, const TexturePtr &diffuse) -> std::pair<unsigned int, TexturedMeshPtr>
{
    auto shader = get_current_texture_shader();
    unsigned int id = static_obj_id++;
    std::map<std::string, TexturePtr> df;
    df["diffuse"] = diffuse;
    auto mesh = std::make_shared<TexturedMesh>(std::move(vertices), std::move(indices), std::move(df));
    auto res = _scene_objects.emplace(id, std::make_shared<SceneObject>(mesh));
    res.first->second->_id = id;
    res.first->second->use_shader(shader);
    _opt.current_object_id = id;
    _opt.object_dirty = true;
    return {id, mesh};
}

auto Kasumi::Scene::add_shader(const std::string &vertex_shader, const std::string &fragment_shader, const std::string &geometry_shader) -> unsigned int
{
    auto res = _scene_shaders.emplace(static_shader_id++, std::make_shared<Shader>(vertex_shader, fragment_shader, geometry_shader));
    return res.first->first;
}

auto Kasumi::Scene::add_camera() -> unsigned int
{
    auto res = _scene_cameras.emplace(static_camera_id++, std::make_shared<Camera>(Camera::Opt()));
    _opt.default_camera_id = res.first->first;
    return res.first->first;
}

void Kasumi::Scene::erase(unsigned int id)
{
    if (_scene_objects_erased.find(id) != _scene_objects_erased.end())
        return;
    _scene_objects_erased.insert({id, std::move(_scene_objects[id])});
    _scene_objects.erase(id);
}

void Kasumi::Scene::restore(unsigned int id)
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
        auto camera = get_current_camera();
        obj.second->update_mvp(camera->get_view(), camera->get_projection());
        obj.second->render();
    }
}

void Kasumi::Scene::set_position(unsigned int id, const mVector3 &position) { _scene_objects[id]->_pose.position = position; }
void Kasumi::Scene::set_rotation(unsigned int id, const mVector3 &rotation) { _scene_objects[id]->_pose.euler = rotation; }
void Kasumi::Scene::set_scale(unsigned int id, const mVector3 &scale) { _scene_objects[id]->_pose.scale = scale; }
auto Kasumi::Scene::get_position(unsigned int id) -> const mVector3 & { return _scene_objects[id]->_pose.position; }
auto Kasumi::Scene::get_rotation(unsigned int id) -> const mVector3 & { return _scene_objects[id]->_pose.euler; }
auto Kasumi::Scene::get_scale(unsigned int id) -> const mVector3 & { return _scene_objects[id]->_pose.scale; }

void Kasumi::Scene::for_each_item(const std::function<void(SceneObjectPtr &)> &func)
{
    for (auto &obj: _scene_objects)
        func(obj.second);
}

auto Kasumi::Scene::get_current_object() -> Kasumi::SceneObjectPtr
{
    if (_opt.object_dirty)
        update();
    return _opt.current_object;
}

auto Kasumi::Scene::get_current_camera() -> Kasumi::CameraPtr
{
    if (_opt.camera_dirty)
        update();
    return _opt.current_camera;
}

auto Kasumi::Scene::get_current_texture_shader() -> Kasumi::ShaderPtr
{
    if (_opt.shader_dirty)
        update();
    return _opt.current_texture_shader;
}

auto Kasumi::Scene::get_current_color_shader() -> Kasumi::ShaderPtr
{
    if (_opt.shader_dirty)
        update();
    return _opt.current_color_shader;
}

void Kasumi::Scene::update()
{
    if (_opt.camera_dirty)
    {
        _opt.current_camera = _scene_cameras.at(_opt.default_camera_id);
        _opt.camera_dirty = false;
    }
    if (_opt.object_dirty)
    {
        _opt.current_object = _scene_objects.at(_opt.current_object_id);
        _opt.object_dirty = false;
    }
    if (_opt.shader_dirty)
    {
        _opt.current_texture_shader = _scene_shaders.at(_opt.default_texture_shader_id);
        _opt.current_color_shader = _scene_shaders.at(_opt.default_color_shader_id);
        _opt.shader_dirty = false;
    }
}

void Kasumi::Scene::key(int key, int scancode, int action, int mods) { get_current_camera()->key(key, scancode, action, mods); }
void Kasumi::Scene::mouse_button(int button, int action, int mods) { get_current_camera()->mouse_button(button, action, mods); }
void Kasumi::Scene::mouse_scroll(double x_offset, double y_offset) { get_current_camera()->mouse_scroll(x_offset, y_offset); }
void Kasumi::Scene::mouse_cursor(double x_pos, double y_pos) { get_current_camera()->mouse_cursor(x_pos, y_pos); }
void Kasumi::Scene::ui_sidebar()
{
    auto selected_object = get_current_object();
    if (selected_object == nullptr)
        return;
    auto sliders = [&](std::string label, mVector3 &data, float sens)
    {
        label += "##" + std::to_string(selected_object->_id);
        ImGui::DragFloat3(label.c_str(), &data[0], sens);
    };
    ImGui::Text("Edit Pose");
    sliders("Position", selected_object->_pose.position, 0.1f);
    sliders("Rotation", selected_object->_pose.euler, 0.1f);
    sliders("Scale", selected_object->_pose.scale, 0.031f);
    static bool wireframe = false;
    ImGui::Checkbox("Wireframe", &wireframe);
    selected_object->set_wireframe(wireframe);
    ImGui::Separator();
}
