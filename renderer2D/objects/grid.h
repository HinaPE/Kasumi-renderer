#ifndef KASUMI_GRID_H
#define KASUMI_GRID_H

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
