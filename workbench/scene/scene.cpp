#include "scene.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "GLFW/glfw3.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

static unsigned static_obj_id = 0;
static unsigned static_shader_id = 0;
static unsigned static_camera_id = 0;

Kasumi::Workbench::Scene::Scene()
{
    _opt.default_texture_shader_id = add_shader(std::string(ShaderDir) + "texture_shader_vertex.glsl", std::string(ShaderDir) + "texture_shader_fragment.glsl");
    _opt.default_color_shader_id = add_shader(std::string(ShaderDir) + "color_shader_vertex.glsl", std::string(ShaderDir) + "color_shader_fragment.glsl");
    _opt.default_camera_id = add_camera(); // default camera
    _opt.camera_dirty = true;
    _opt.shader_dirty = true;
    update();
}

Kasumi::Workbench::Scene::~Scene()
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

auto Kasumi::Workbench::Scene::read_scene(const std::string &path) -> std::string
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
            Kasumi::mVector3 position, rotation, scale = mVector3(1, 1, 1);
            Kasumi::mVector3 color;
            std::string attrib;

            unsigned int obj_id = std::numeric_limits<unsigned int>::max();
            while (iss >> attrib)
            {
                if (attrib == "path")
                {
                    iss >> model_path;
                    obj_id = add_model(model_path);
                } else if (attrib == "Hatsune_Miku_V4X")
                    obj_id = add_model(std::string(ModelDir) + "Hatsune_Miku_V4X/Hatsune_Miku_V4X.pmx");
                else if (attrib == "cube" || attrib == "sphere" || attrib == "cylinder")
                    obj_id = add_primitive(attrib);
                else if (attrib == "shader")
                    iss >> shader_name;
                else if (attrib == "position")
                    iss >> position.x >> position.y >> position.z;
                else if (attrib == "rotation")
                    iss >> rotation.x >> rotation.y >> rotation.z;
                else if (attrib == "scale")
                    iss >> scale.x >> scale.y >> scale.z;
                else if (attrib == "color")
                    iss >> color.x >> color.y >> color.z;
            }
            if (obj_id == std::numeric_limits<unsigned int>::max())
                continue;
            auto obj = _scene_objects[obj_id];
            obj->_pose.position = position;
            obj->_pose.euler = rotation;
            obj->_pose.scale = scale;
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

auto Kasumi::Workbench::Scene::write_to_file(const std::string &path) -> std::string
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

void Kasumi::Workbench::Scene::key(int key, int scancode, int action, int mods) { get_current_camera()->key(key, scancode, action, mods); }
void Kasumi::Workbench::Scene::mouse_button(int button, int action, int mods) { get_current_camera()->mouse_button(button, action, mods); }
void Kasumi::Workbench::Scene::mouse_scroll(double x_offset, double y_offset) { get_current_camera()->mouse_scroll(x_offset, y_offset); }
void Kasumi::Workbench::Scene::mouse_cursor(double x_pos, double y_pos) { get_current_camera()->mouse_cursor(x_pos, y_pos); }

void Kasumi::Workbench::Scene::erase(unsigned int id)
{
    if (_scene_objects_erased.find(id) != _scene_objects_erased.end())
        return;
    _scene_objects_erased.insert({id, std::move(_scene_objects[id])});
    _scene_objects.erase(id);
}

void Kasumi::Workbench::Scene::restore(unsigned int id)
{
    if (_scene_objects.find(id) != _scene_objects.end())
        return;
    _scene_objects.insert({id, std::move(_scene_objects[id])});
    _scene_objects_erased.erase(id);
}

void Kasumi::Workbench::Scene::render()
{
    for (auto &obj: _scene_objects)
    {
        auto camera = get_current_camera();
        obj.second->update_mvp(camera->get_view(), camera->get_projection());
        obj.second->render();
    }
}

void Kasumi::Workbench::Scene::for_each_item(const std::function<void(SceneObjectPtr &)> &func)
{
    for (auto &obj: _scene_objects)
        func(obj.second);
}

auto Kasumi::Workbench::Scene::get_current_object() -> Kasumi::Workbench::SceneObjectPtr
{
    if (!_opt.object_dirty)
        return _opt.current_object;
    auto co = _scene_objects.at(_opt.current_object_id);
    _opt.current_object = co;
    _opt.object_dirty = false;
    return co;
}

auto Kasumi::Workbench::Scene::get_current_camera() -> Kasumi::CameraPtr
{
    if (!_opt.camera_dirty)
        return _opt.current_camera;
    auto cc = _scene_cameras.at(_opt.default_camera_id);
    _opt.current_camera = cc;
    _opt.camera_dirty = false;
    return cc;
}

auto Kasumi::Workbench::Scene::get_current_texture_shader() -> Kasumi::ShaderPtr
{
    if (!_opt.shader_dirty)
        return _opt.current_texture_shader;
    auto cs = _scene_shaders.at(_opt.default_texture_shader_id);
    _opt.current_texture_shader = cs;
    _opt.shader_dirty = false;
    return cs;
}

auto Kasumi::Workbench::Scene::get_current_color_shader() -> Kasumi::ShaderPtr
{
    if (!_opt.shader_dirty)
        return _opt.current_color_shader;
    auto cs = _scene_shaders.at(_opt.default_color_shader_id);
    _opt.current_color_shader = cs;
    _opt.shader_dirty = false;
    return cs;
}

auto Kasumi::Workbench::Scene::add_model(const std::string &model_path, unsigned int shader_id) -> unsigned int
{
    std::shared_ptr<Shader> shader = nullptr;
    if (shader_id != 0)
        shader = _scene_shaders.find(shader_id)->second;
    else
        shader = get_current_texture_shader();
    unsigned int id = static_obj_id++;
    auto res = _scene_objects.emplace(id, std::make_shared<SceneObject>(std::make_shared<Model>(model_path, shader)));
    if (!res.second)
        return std::numeric_limits<unsigned int>::max();
    res.first->second->_id = id;
    res.first->second->use_shader(shader);
    return id;
}

auto Kasumi::Workbench::Scene::add_primitive(const std::string &primitive_name, unsigned int shader_id) -> unsigned int { return add_model(std::string(ModelDir) + primitive_name + ".obj", _opt.default_texture_shader_id /* TODO: */); }

auto Kasumi::Workbench::Scene::add_shader(const std::string &vertex_shader, const std::string &fragment_shader, const std::string &geometry_shader) -> unsigned int
{
    auto res = _scene_shaders.emplace(static_shader_id++, std::make_shared<Shader>(vertex_shader, fragment_shader, geometry_shader));
    return res.first->first;
}

auto Kasumi::Workbench::Scene::add_camera() -> unsigned int
{
    auto res = _scene_cameras.emplace(static_camera_id++, std::make_shared<Camera>(Camera::Opt()));
    _opt.default_camera_id = res.first->first;
    return res.first->first;
}

void Kasumi::Workbench::Scene::update()
{
    if (_opt.camera_dirty)
        _opt.current_camera = _scene_cameras.at(_opt.default_camera_id);
    if (_opt.object_dirty)
        _opt.current_object = _scene_objects.at(_opt.current_object_id);
    if (_opt.shader_dirty)
    {
        _opt.current_texture_shader = _scene_shaders.at(_opt.default_texture_shader_id);
        _opt.current_color_shader = _scene_shaders.at(_opt.default_color_shader_id);
    }
}
