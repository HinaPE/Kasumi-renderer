#include "manager.h"
#include "simulate.h"

#include <memory>
#include <utility>
#include "imgui.h"

Kasumi::Manager::Manager(ScenePtr scene) : _scene(std::move(scene))
{
	auto simulate = std::make_shared<Simulate>(1500, 700);
	load_api(simulate);
}
void Kasumi::Manager::load_api(const Kasumi::GuiPtr &gui)
{
	gui->_scene = _scene;
	_gui.emplace_back(gui);
}
void Kasumi::Manager::render(const ScenePtr &scene, float &start_x, float &start_y) { for (auto &gui: _gui) gui->render(); }
auto Kasumi::Manager::quit() -> bool { return false; }
void Kasumi::Manager::key(int key, int scancode, int action, int mods) { for (auto &gui: _gui) gui->key(key, scancode, action, mods); }
void Kasumi::Manager::mouse_button(int button, int action, int mods) { for (auto &gui: _gui) gui->mouse_button(button, action, mods); }
void Kasumi::Manager::mouse_scroll(double x_offset, double y_offset) { for (auto &gui: _gui) gui->mouse_scroll(x_offset, y_offset); }
void Kasumi::Manager::mouse_cursor(double x_pos, double y_pos) { for (auto &gui: _gui) gui->mouse_cursor(x_pos, y_pos); }
