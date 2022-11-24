#include "scene_object.h"
#include "imgui.h"

void Kasumi::SceneObject::render()
{
    auto get_unique_str = [&](const std::string &str) -> std::string
    {
        return str + std::to_string(_id);
    };
//    ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
//    ImGui::SliderFloat3(get_unique_str("position").c_str(), &_pose.position[0], -20.0f, 20.0f, "%.2f");
//    ImGui::SliderFloat3(get_unique_str("rotation").c_str(), &_pose.euler[0], -180.0f, 180.0f, "%.2f");
//    ImGui::SliderFloat3(get_unique_str("scale").c_str(), &_pose.scale[0], 0.0f, 1.0f, "%.2f");
//    ImGui::End();
    std::visit([&](auto &renderable) { renderable->render(); }, _underlying);
}

void Kasumi::SceneObject::update_mvp(const Kasumi::mMatrix4x4 &view, const Kasumi::mMatrix4x4 &projection)
{
    std::visit([&](auto &renderable)
               {
                   auto shader = renderable->get_shader();
                   shader->use();
                   auto model = _pose.get_model_matrix();
                   shader->uniform("projection", projection);
                   shader->uniform("view", view);
                   shader->uniform("model", model);
               }, _underlying);
}

void Kasumi::SceneObject::use_shader(const Kasumi::ShaderPtr &shader)
{
    std::visit([&](auto &renderable) { renderable->use_shader(shader); }, _underlying);
}
