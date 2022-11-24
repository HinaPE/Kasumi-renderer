#include "app.h"

#include <utility>
#include "nfd/nfd.h"
#include "imgui/imgui.h"

Kasumi::Renderer::Renderer(std::string scene) : App(scene), _scene(std::move(std::make_shared<Scene>())), _manager(std::move(std::make_shared<Manager>())), _undo(std::move(std::make_shared<Undo>())), _apis() {}

void Kasumi::Renderer::load_api(const Kasumi::ApiPtr &api) { _apis.emplace_back(api); }
void Kasumi::Renderer::prepare() { _scene->read_scene(std::string(SceneDir) + _scene_name); }
void Kasumi::Renderer::update(double dt)
{
    for (auto &api: _apis)
        api->step(_scene, dt);
    reset_state();
    ui_menu();
    ui_sidebar();
    _scene->render();
    _manager->render(_scene, _next_x, _next_y);
}
auto Kasumi::Renderer::quit() -> bool { return _manager->quit(); }
void Kasumi::Renderer::key(int key, int scancode, int action, int mods)
{
    _scene->key(key, scancode, action, mods);
    _manager->key(key, scancode, action, mods);
}
void Kasumi::Renderer::mouse_button(int button, int action, int mods)
{
    _scene->mouse_button(button, action, mods);
    _manager->mouse_button(button, action, mods);
}
void Kasumi::Renderer::mouse_scroll(double x_offset, double y_offset)
{
    _scene->mouse_scroll(x_offset, y_offset);
    _manager->mouse_scroll(x_offset, y_offset);
}
void Kasumi::Renderer::mouse_cursor(double x_pos, double y_pos)
{
    _scene->mouse_cursor(x_pos, y_pos);
    _manager->mouse_cursor(x_pos, y_pos);
}
void Kasumi::Renderer::ui_menu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Scene (Ctrl+o)"))
            {
                char *scene_file = nullptr;
                auto res = NFD_OpenDialog("txt", SceneDir, &scene_file);
                if (res == NFD_OKAY)
                {
                    _scene = nullptr;
                    _scene = std::move(std::make_shared<Scene>()); // discard previous scene and construct a new one
                    _scene->read_scene(std::string(scene_file));
                    std::cout << "Success" << std::endl;
                } else if (res == NFD_CANCEL)
                    std::cout << "Cancel" << std::endl;
                else
                    std::cout << "Error" << std::endl;
            }
            if (ImGui::MenuItem("Export Scene (Ctrl+e)"))
                std::cout << std::endl;
            if (ImGui::MenuItem("Save Scene (Ctrl+s)"))
                std::cout << std::endl;
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo (Ctrl+z)"))
                std::cout << std::endl;
            if (ImGui::MenuItem("Redo (Ctrl+y)"))
                std::cout << std::endl;
            if (ImGui::MenuItem("Edit Debug Data (Ctrl+d)"))
                std::cout << std::endl;
            if (ImGui::MenuItem("Settings"))
                std::cout << std::endl;
            ImGui::EndMenu();
        }

        ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);

        _next_x = 0.f;
        _next_y = ImGui::GetWindowSize().y;
        ImGui::EndMainMenuBar();
    }
}
void Kasumi::Renderer::ui_sidebar()
{
    ImGui::SetNextWindowPos({_next_x, _next_y});
    ImGui::SetNextWindowSizeConstraints({ImGui::GetIO().DisplaySize.x / 4.75f, ImGui::GetIO().DisplaySize.y - _next_y}, {ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - _next_y});
    ImGui::Begin("Monitor", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing);
    for (auto &api: _apis)
    {
        api->ui_sidebar(_scene);
        ImGui::Separator();
    }
    _next_x += ImGui::GetWindowSize().x;
    ImGui::End();
}
void Kasumi::Renderer::reset_state()
{
    _next_x = 0;
    _next_y = 0;
}