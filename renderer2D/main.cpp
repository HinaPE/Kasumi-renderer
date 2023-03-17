#include "renderer2D.h"

auto main() -> int
{
	std::make_shared<Renderer2D>()->launch();
	return 0;
}