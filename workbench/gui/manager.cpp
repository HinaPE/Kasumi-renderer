#include "manager.h"

Kasumi::Workbench::Manager::Manager()
{
    _gui.emplace("Simulate", std::move(std::make_shared<Simulate>()));
}

void Kasumi::Workbench::Manager::render()
{
    for (auto &gui: _gui)
        gui.second->render();
}

void Kasumi::Workbench::Manager::event(GLFWwindow *window)
{
    for (auto &gui: _gui)
        gui.second->event(window);
}
