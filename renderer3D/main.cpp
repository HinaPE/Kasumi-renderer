#include "renderer3D.h"

auto main() -> int
{
	std::make_shared<Kasumi::Renderer3D>()->launch();
	return 0;
}