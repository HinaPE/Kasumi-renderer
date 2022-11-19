#include "scene.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

static unsigned static_obj_id = 0;
static unsigned static_shader_id = 0;
static unsigned static_camera_id = 0;

Kasumi::Workbench::Scene::Scene()
{
    opt.default_shader_id = add_shader(std::string(ShaderDir) + "default_shader_vertex.glsl", std::string(ShaderDir) + "default_shader_fragment.glsl"); // default shader
    opt.default_camera_id = add_camera(); // default camera
}

Kasumi::Workbench::Scene::~Scene()
{
    _scene_objects.clear();
    _scene_objects_erased.clear();
    _scene_cameras.clear();
    _scene_shaders.clear();

    opt.default_camera_id = std::numeric_limits<unsigned int>::max();
    opt.current_object_id = std::numeric_limits<unsigned int>::max();

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
            Kasumi::mVector3 position, rotation, scale;
            std::string attrib;
            while (iss >> attrib)
            {
                if (attrib == "path")
                    iss >> model_path;
                else if (attrib == "shader")
                    iss >> shader_name;
                else if (attrib == "position")
                    iss >> position.x >> position.y >> position.z;
                else if (attrib == "rotation")
                    iss >> rotation.x >> rotation.y >> rotation.z;
                else if (attrib == "scale")
                    iss >> scale.x >> scale.y >> scale.z;
            }
            auto id = add_model(model_path);
//            auto obj = _scene_objects[id];
//            obj->_pose.position = position;
//            obj->_pose.euler = rotation;
//            obj->_pose.scale = scale;
        } else if (type == "shader")
        {
            std::string vertex_shader;
            std::string fragment_shader;
            std::string geometry_shader;
            if (!(iss >> vertex_shader >> fragment_shader >> geometry_shader))
                continue;
            add_shader(vertex_shader, fragment_shader, geometry_shader);
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

auto Kasumi::Workbench::Scene::get_current_object() const -> Kasumi::Workbench::SceneObjectPtr
{
    if (_scene_objects.contains(opt.current_object_id))
        return _scene_objects.at(opt.current_object_id);

    std::cout << "NO OBJECT SELECTED" << std::endl;
    return nullptr;
}

auto Kasumi::Workbench::Scene::get_current_camera() const -> Kasumi::CameraPtr
{
    if (_scene_cameras.contains(opt.default_camera_id))
        return _scene_cameras.at(opt.default_camera_id);

    std::cout << "NO CAMERA" << std::endl;
    return nullptr;
}

auto Kasumi::Workbench::Scene::add_model(const std::string &model_path, unsigned int shader_id) -> unsigned int
{
    auto shader = _scene_shaders.find(shader_id)->second;
    auto res = _scene_objects.emplace(static_obj_id++, std::make_shared<SceneObject>(std::make_shared<Model>(model_path, shader)));
    res.first->second->use_shader(shader);
    return res.first->first;
}

auto Kasumi::Workbench::Scene::add_shader(const std::string &vertex_shader, const std::string &fragment_shader, const std::string &geometry_shader) -> unsigned int
{
    auto res = _scene_shaders.emplace(static_shader_id++, std::make_shared<Shader>(vertex_shader, fragment_shader, geometry_shader));
    return res.first->first;
}

auto Kasumi::Workbench::Scene::add_camera() -> unsigned int
{
    auto res = _scene_cameras.emplace(static_camera_id++, std::make_shared<Camera>(Camera::Opt()));
    opt.default_camera_id = res.first->first;
    return res.first->first;
}
