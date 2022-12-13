#include "manager.h"
#include "imgui.h"

Kasumi::Manager::Manager() = default;
void Kasumi::Manager::render(const ScenePtr &scene, float &start_x, float &start_y)
{
//    ImGui::SetNextWindowPos({start_x, start_y});
//    ImGui::SetNextWindowSizeConstraints({ImGui::GetIO().DisplaySize.x / 4.75f, ImGui::GetIO().DisplaySize.y - start_y}, {ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - start_y});
//    ImGui::Begin("mMonitor", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing);
//    ImGui::Text("Edit Scene");
//    scene->render();
//    for (auto &gui: _gui)
//        gui.second->render();
//    ImGui::End();
}
auto Kasumi::Manager::quit() -> bool
{
	return false;
}
void Kasumi::Manager::key(int key, int scancode, int action, int mods)
{
	for (auto &gui: _gui)
		gui.second->key(key, scancode, action, mods);
}
void Kasumi::Manager::mouse_button(int button, int action, int mods)
{
	for (auto &gui: _gui)
		gui.second->mouse_button(button, action, mods);
}
void Kasumi::Manager::mouse_scroll(double x_offset, double y_offset)
{
	for (auto &gui: _gui)
		gui.second->mouse_scroll(x_offset, y_offset);
}
void Kasumi::Manager::mouse_cursor(double x_pos, double y_pos)
{
	for (auto &gui: _gui)
		gui.second->mouse_cursor(x_pos, y_pos);
}
