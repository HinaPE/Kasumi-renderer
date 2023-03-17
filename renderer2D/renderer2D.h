#ifndef HINAPE_RENDERER2D_H
#define HINAPE_RENDERER2D_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/api.h"
#include "scene.h"

class Renderer2D : public Kasumi::App
{
public:
	Renderer2D() { clean_mode(); dark_mode(); }

protected:
	void prepare() final
	{
		_scene = std::make_shared<Kasumi::Scene2D>();
		auto rectangle = std::make_shared<Kasumi::Rectangle2DObject>();
		auto circle = std::make_shared<Kasumi::Circle2DObject>();
		rectangle->POSE.position = mVector2(-200, 0);
		circle->POSE.position = mVector2(200, 0);
		_scene->add(circle);
		_scene->add(rectangle);
	}
	void update(double dt) final
	{
		_scene->draw();
	}

private:
	Kasumi::Scene2DPtr _scene;
};

#endif //HINAPE_RENDERER2D_H
