#include "deferred_renderer3D.h"

void Kasumi::DeferredRenderer3D::add_object(const Kasumi::ObjectMesh3DPtr &object) { _objects[object->ID] = object; }
void Kasumi::DeferredRenderer3D::prepare()
{
	App::prepare();
}
void Kasumi::DeferredRenderer3D::update(double dt)
{
	App::update(dt);
}
bool Kasumi::DeferredRenderer3D::quit()
{
	return App::quit();
}
void Kasumi::DeferredRenderer3D::key(int key, int scancode, int action, int mods)
{
	App::key(key, scancode, action, mods);
}
void Kasumi::DeferredRenderer3D::mouse_button(int button, int action, int mods)
{
	App::mouse_button(button, action, mods);
}
void Kasumi::DeferredRenderer3D::mouse_scroll(double x_offset, double y_offset)
{
	App::mouse_scroll(x_offset, y_offset);
}
void Kasumi::DeferredRenderer3D::mouse_cursor(double x_pos, double y_pos)
{
	App::mouse_cursor(x_pos, y_pos);
}
