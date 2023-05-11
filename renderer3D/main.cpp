#include "renderer3D.h"

auto main() -> int
{
	Kasumi::Renderer3D::DEFAULT_RENDERER.clean_mode();
	Kasumi::Renderer3D::DEFAULT_RENDERER.launch();
	return 0;
}
