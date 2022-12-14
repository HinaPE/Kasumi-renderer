#include "simulate.h"
#include "imgui.h"

Kasumi::Simulate::Simulate(int width, int height) : _debug_frame(std::make_shared<Framebuffer>(width, height, 0.4, 0.2, 1.0, 1.0)) { _debug_frame->render_callback = [&]() {}; }

void Kasumi::Simulate::render()
{
	// draw call: render the world to the debug framebuffer
	_debug_frame->use();
	for (auto &o: _scene->_scene_objects)
		o.second->framebuffer_mode(true);
	_scene->render();
	for (auto &o: _scene->_scene_objects)
		o.second->framebuffer_mode(false);

	// draw call: render the debug framebuffer to the main window
	_debug_frame->unuse();
	_debug_frame->render();
}