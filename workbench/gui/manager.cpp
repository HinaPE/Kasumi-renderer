#include "manager.h"
#include <iostream>

Kasumi::Workbench::Manager::Manager()
{
    _gui.emplace("Simulate", std::move(std::make_shared<Simulate>()));
}

void Kasumi::Workbench::Manager::key(int key, int scancode, int action, int mods)
{

}
void Kasumi::Workbench::Manager::mouse_button(int button, int action, int mods)
{

}
void Kasumi::Workbench::Manager::mouse_scroll(double x_offset, double y_offset)
{

}
void Kasumi::Workbench::Manager::mouse_cursor(double x_pos, double y_pos)
{

}

void Kasumi::Workbench::Manager::render()
{
    for (auto &gui: _gui)
        gui.second->render();
}
