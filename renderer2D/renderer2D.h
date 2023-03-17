#ifndef HINAPE_RENDERER2D_H
#define HINAPE_RENDERER2D_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/api.h"
#include "scene.h"

// @formatter:off
namespace Kasumi
{
class Renderer2D : public App
{
public:
	Renderer2D() { clean_mode(); _scene = std::make_shared<Kasumi::Scene2D>(); }
	std::function<void(const Kasumi::Scene2DPtr &)> _init;
	std::function<void(real)> _step;
	std::function<void()> _debugger;
	std::function<void(int key, int scancode, int action, int mods)> _key;

protected:
	void prepare() final
	{
		if(_init)
			_init(_scene);
	}
	void update(double dt) final
	{
		_scene->draw();
	}

private:
	Kasumi::Scene2DPtr _scene;
};
} // namespace Kasumi

#endif //HINAPE_RENDERER2D_H
