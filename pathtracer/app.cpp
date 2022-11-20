#include "app.h"

#include <utility>
Kasumi::Pathtracer::App::App(std::string scene) : Kasumi::App(std::move(scene)) {}
void Kasumi::Pathtracer::App::prepare()
{

}
void Kasumi::Pathtracer::App::render()
{

}
bool Kasumi::Pathtracer::App::quit()
{
    return false;
}
void Kasumi::Pathtracer::App::key(int key, int scancode, int action, int mods)
{

}
void Kasumi::Pathtracer::App::mouse_button(int button, int action, int mods)
{

}
void Kasumi::Pathtracer::App::mouse_scroll(double x_offset, double y_offset)
{

}
void Kasumi::Pathtracer::App::mouse_cursor(double x_pos, double y_pos)
{

}
