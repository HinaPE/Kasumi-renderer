#include "simulate.h"
#include "imgui.h"

Kasumi::Simulate::Simulate(int width, int height) : _debug_frame(std::make_shared<Framebuffer>(width, height, 0.4, 0.2, 1.0, 1.0))
{
	_debug_frame->render_callback = [&]()
	{
		// draw call: render the world to the debug framebuffer
		for (auto &o: _scene->_scene_objects)
			o.second->debug_frame_mode(true);
		_scene->render();
		for (auto &o: _scene->_scene_objects)
			o.second->debug_frame_mode(false);
	};
}

void Kasumi::Simulate::render()
{
	// draw call: render the debug framebuffer onto the main window
	_debug_frame->render();
}