#include "app.h"
#include "nfd/nfd.h"
#include "imgui/imgui.h"

Kasumi::Workbench::App::App() : _scene(std::move(std::make_shared<Scene>())), _manager(std::move(std::make_shared<Manager>())), _undo(std::move(std::make_shared<Undo>())) {}

void Kasumi::Workbench::App::prepare()
{
    _scene->read_scene(std::string(TestDir) + "scene.txt");
}

void Kasumi::Workbench::App::render()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Scene (Ctrl+o)"))
            {
                char *scene_file = nullptr;
                auto res = NFD_OpenDialog("txt", TestDir, &scene_file);
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
        ImGui::EndMainMenuBar();
    }
    _scene->render();
    _manager->render();
}

void Kasumi::Workbench::App::event(GLFWwindow *window)
{
    Kasumi::App::event(window);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        std::cout << "Hello Kasumi" << std::endl;
    _manager->event(window);
}
