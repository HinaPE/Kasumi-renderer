#ifndef KASUMI_GRID_H
#define KASUMI_GRID_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object2D.h"

namespace Kasumi
{
class Grid2DObject : public Object2D, public Renderable
{
protected:
	void _draw() final;
};
} // namespace Kasumi

#endif //KASUMI_GRID_H
