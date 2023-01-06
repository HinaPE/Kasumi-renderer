#include "app.h"

#include "GLFW/glfw3.h"
#include "nfd/nfd.h"
#include "imgui/imgui.h"

#include <utility>

Kasumi::Renderer::Renderer(std::string scene_file, int width, int height, const std::string &title)
		: App(width, height, title), _scene_file(std::move(scene_file)), _scene(std::move(std::make_shared<Scene>()))
{
	_manager = std::move(std::make_shared<Manager>(_scene));
}

auto Kasumi::Renderer::load_api(const Kasumi::ApiPtr &api) -> std::shared_ptr<Kasumi::App>
{
	api->_scene = _scene;
	_apis.emplace_back(api);
	return shared_from_this();
}
void Kasumi::Renderer::prepare()
{
	_scene->read_scene(std::string(SceneDir) + _scene_file);
	for (auto &api: _apis)
		api->prepare();
}
void Kasumi::Renderer::update(double dt)
{
	// update plugin api scene (physics scene)
	if (_opt.api_running)
		for (auto &api: _apis)
			api->step(dt);

	// render ui
	reset_state();
	ui_menu();
	ui_sidebar();

	_scene->render(); // draw call: render the world to the main window
	_manager->render(_scene, _next_x, _next_y);
}
auto Kasumi::Renderer::quit() -> bool { return _manager->quit(); }
void Kasumi::Renderer::key(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		_opt.api_running = !_opt.api_running;
	_manager->key(key, scancode, action, mods);
	_scene->key(key, scancode, action, mods);
	for (auto &api: _apis)
		api->key(key, scancode, action, mods);
}
void Kasumi::Renderer::mouse_button(int button, int action, int mods)
{
	_manager->mouse_button(button, action, mods);
	_scene->mouse_button(button, action, mods);
	for (auto &api: _apis)
		api->mouse_button(button, action, mods);
}
void Kasumi::Renderer::mouse_scroll(double x_offset, double y_offset)
{
	_manager->mouse_scroll(x_offset, y_offset);
	_scene->mouse_scroll(x_offset, y_offset);
	for (auto &api: _apis)
		api->mouse_scroll(x_offset, y_offset);
}
void Kasumi::Renderer::mouse_cursor(double x_pos, double y_pos)
{
	_manager->mouse_cursor(x_pos, y_pos);
	_scene->mouse_cursor(x_pos, y_pos);
	for (auto &api: _apis)
		api->mouse_cursor(x_pos, y_pos);
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

		if (ImGui::BeginMenu("Pathtracer"))
		{
			if (ImGui::MenuItem("Load Pathtracer"))
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
	ImGui::SetNextWindowSizeConstraints({ImGui::GetIO().DisplaySize.x / 5.75f, ImGui::GetIO().DisplaySize.y - _next_y}, {ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y - _next_y});
	ImGui::Begin("Monitor", nullptr, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing);
	_scene->ui_sidebar();
	ImGui::Separator();
	for (auto &api: _apis)
	{
		api->ui_sidebar();
		ImGui::Separator();
	}
	ImGui::Text("Shortcuts");
	ImGui::BeginDisabled(true);
	ImGui::Checkbox("Space: start/stop sim", &_opt.api_running);
	ImGui::EndDisabled();
	ImGui::Text("W: wireframe mode");
	_next_x += ImGui::GetWindowSize().x;
	ImGui::End();
}
void Kasumi::Renderer::reset_state()
{
	_next_x = 0;
	_next_y = 0;
}
