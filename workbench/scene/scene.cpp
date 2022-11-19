#include "scene.h"
#include <iostream>

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
        obj.second->update_mvp(mMatrix4x4::makeIdentity(), mMatrix4x4::makeIdentity());
//        obj.second->update_mvp(camera->get_view(), camera->get_projection());
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
    if (_scene_cameras.contains(opt.current_camera_id))
        return _scene_cameras.at(opt.current_camera_id);

    std::cout << "NO CAMERA" << std::endl;
    return nullptr;
}

auto Kasumi::Workbench::Scene::add_model(const std::string &model_path, unsigned int shader_id) -> unsigned int
{
    static unsigned static_obj_id = 0;
    auto shader = _scene_shaders.find(shader_id)->second;
    auto res = _scene_objects.emplace(static_obj_id++, std::make_shared<SceneObject>(std::make_shared<Model>(model_path, shader)));
    res.first->second->use_shader(shader);
    return res.first->first;
}

auto Kasumi::Workbench::Scene::add_shader(const std::string &vertex_shader, const std::string &fragment_shader, const std::string &geometry_shader) -> unsigned int
{
    static unsigned static_shader_id = 0;
    auto res = _scene_shaders.emplace(static_shader_id++, std::make_shared<Shader>(vertex_shader, fragment_shader, geometry_shader));
    return res.first->first;
}

auto Kasumi::Workbench::Scene::add_camera() -> unsigned int
{
    static unsigned static_camera_id = 0;
    auto res = _scene_cameras.emplace(static_camera_id++, std::make_shared<Camera>(mVector2(1024, 768)));
    opt.current_camera_id = res.first->first;
    return res.first->first;
}
