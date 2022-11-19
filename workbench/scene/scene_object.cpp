#include "scene_object.h"
#include <imgui.h>

void Kasumi::Workbench::SceneObject::render()
{
    static real scale = 1;
    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SliderFloat3("position", &_pose.position[0], -20.0f, 20.0f, "%.2f");
    ImGui::SliderFloat3("rotation", &_pose.euler[0], -180.0f, 180.0f, "%.2f");
    ImGui::SliderFloat("scale", &scale, 0.0f, 1.0f, "%.2f");
    ImGui::End();
    _pose.scale.set(scale, scale, scale);
    std::visit([](auto &&renderable) { renderable->render(); }, _underlying);
}

void Kasumi::Workbench::SceneObject::update_mvp(const Kasumi::mMatrix4x4 &view, const Kasumi::mMatrix4x4 &projection)
{
    std::visit([&](auto &&renderable)
               {
                   auto shader = renderable->get_shader();
                   auto model = _pose.get_model_matrix();
                   shader->uniform("projection", projection);
                   shader->uniform("view", view);
                   shader->uniform("model", model);
               }, _underlying);
}

void Kasumi::Workbench::SceneObject::use_shader(const Kasumi::ShaderPtr &shader)
{
    std::visit([&](auto &&renderable) { renderable->use_shader(shader); }, _underlying);
}
