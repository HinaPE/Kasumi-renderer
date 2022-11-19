#include "scene_object.h"

void Kasumi::Workbench::SceneObject::render()
{
    std::visit([](auto &&renderable) { renderable->render(); }, _underlying);
}

void Kasumi::Workbench::SceneObject::update_mvp(const Kasumi::mMatrix4x4 &view, const Kasumi::mMatrix4x4 &projection)
{
    std::visit([&](auto &&renderable)
               {
                   auto shader = renderable->get_shader();
                   shader->uniform("projection", projection);
                   shader->uniform("view", view);
                   shader->uniform("model", pose.get_model_matrix());
               }, _underlying);
}
