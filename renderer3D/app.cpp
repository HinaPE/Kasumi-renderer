#include "app.h"
auto Kasumi::Renderer3D::instance() -> const Kasumi::Renderer3D &
{
	static Kasumi::Renderer3D INSTANCE;
	return INSTANCE;
}
