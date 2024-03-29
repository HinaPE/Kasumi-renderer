#ifndef HINAPE_RENDERER3D_H
#define HINAPE_RENDERER3D_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "GLFW/glfw3.h"
#include "scene.h"

// @formatter:off
namespace Kasumi
{
class Renderer3D : public App
{
public:
	static Renderer3D DEFAULT_RENDERER; // Default Instance of Renderer3D

public:
	Renderer3D() : _scene(std::make_shared<Kasumi::Scene3D>()) {}
	std::function<void(const Kasumi::Scene3DPtr &)> _init;
	std::function<void(real)> _step;
	std::function<void()> _debugger;
	std::function<void(int key, int scancode, int action, int mods)> _key;
	std::function<bool(void)> _quit;

protected:
	void prepare() final
	{
		ObjectLines3D::Init();
		ObjectPoints3D::Init();
		if (_init) _init(_scene);
		inspect(_scene.get());
		_scene->VALID_CHECK();
	}
	void update(double dt) final
	{
		if (_step) HINA_TRACK(if(_running) _step(dt), "Step")
		if(_debugger) _debugger();
		HINA_TRACK(_scene->draw(), "Rendering")
	}
	auto quit() -> bool override 									{ if(_quit) return _quit(); return false; }
	void key(int key, int scancode, int action, int mods) override 	{ _scene->key(key, scancode, action, mods); _debug_key(key, scancode, action, mods); if(_key) _key(key, scancode, action, mods);}
	void mouse_button(int button, int action, int mods) override 	{ _scene->mouse_button(button, action, mods); }
	void mouse_cursor(double x_pos, double y_pos) override 			{ _scene->mouse_cursor(x_pos, y_pos); }
	void ui_menu() override;

protected:
	Kasumi::Scene3DPtr _scene;

private:
	void _debug_key(int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
			_running = !_running;
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
			_step(0.02);
	}
	bool _running = false;
};
using Renderer3DPtr = std::shared_ptr<Renderer3D>;
} // namespace Kasumi
// @formatter:on
#endif //HINAPE_RENDERER3D_H
