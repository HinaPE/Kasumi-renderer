#include "simulate.h"
#include <imgui/imgui.h>

void Kasumi::Workbench::Simulate::render()
{
    ImGui::Begin("Simulate");
    ImGui::Text("Hello, world!");
    ImGui::End();
}

void Kasumi::Workbench::Simulate::event(GLFWwindow *window) {}
