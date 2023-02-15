#ifndef KASUMI_APP_H
#define KASUMI_APP_H

#include "camera.h"
#include "mesh.h"

namespace Kasumi
{
class Renderer3D
{
public:
	static auto instance() -> const Renderer3D &;

	struct Opt
	{
	} _opt;
};
} // namespace Kasumi

#endif //KASUMI_APP_H
