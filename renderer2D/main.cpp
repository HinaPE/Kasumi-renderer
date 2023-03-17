#include "renderer2D.h"

auto main() -> int
{
	auto renderer = std::make_shared<Kasumi::Renderer2D>();

	renderer->_init = [&](const Kasumi::Scene2DPtr &scene)
	{
		auto rectangle = std::make_shared<Kasumi::Rectangle2DObject>();
		auto circle = std::make_shared<Kasumi::Circle2DObject>();
		rectangle->POSE.position = mVector2(-200, 0);
		circle->POSE.position = mVector2(200, 0);
		scene->add(circle);
		scene->add(rectangle);
	};

	renderer->dark_mode();
	renderer->launch();
	return 0;
}