#include "scene.h"
#include <iostream>

static auto next_id() -> unsigned int
{
    static unsigned int id = 0;
    return id++;
}

auto Kasumi::Workbench::Scene::add(Kasumi::Workbench::SceneObjectPtr &&ptr) -> unsigned int
{
    auto id = next_id();
    _scene_objects.emplace(id, std::forward<SceneObjectPtr>(ptr));
    return id;
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
    return nullptr;
}

auto Kasumi::Workbench::Scene::get_current_camera() const -> Kasumi::CameraPtr
{
    if (_scene_cameras.contains(opt.current_camera_id))
        return _scene_cameras.at(opt.current_camera_id);

    std::cout << "NO CAMERA" << std::endl;
    return nullptr;
}
