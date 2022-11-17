#include "scene_object.h"

void Kasumi::Workbench::SceneObject::render()
{
    std::visit([](auto &&renderable) { renderable->render(); }, _underlying);
}
