#include "manager.h"
#include <imgui/imgui.h>
#include <iostream>

Kasumi::Workbench::Manager::Manager()
{
    _gui.emplace("Simulate", std::move(std::make_shared<Simulate>()));
}

void Kasumi::Workbench::Manager::render()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Scene (Ctrl+o)"))
                std::cout << std::endl;
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
    for (auto &gui: _gui)
        gui.second->render();
}

void Kasumi::Workbench::Manager::event(GLFWwindow *window)
{
    for (auto &gui: _gui)
        gui.second->event(window);
}
