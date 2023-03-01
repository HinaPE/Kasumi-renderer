#ifndef KASUMI_GRID_H
#define KASUMI_GRID_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"
#include "geom/grid.h"

namespace Kasumi
{
class GridObject final : public Object3D, public Renderable
{
public:
	struct Opt
	{
		mVector3 color = HinaPE::Color::PURPLE;
	} _opt;
	GridObject();
	void init(const HinaPE::Geom::Grid3Ptr &grid);
	void update();

protected:
	void _draw() final;

private:
	HinaPE::Geom::Grid3Ptr _grid;
	std::vector<Pose> _poses;
	std::shared_ptr<InstancedLines> _grids;
};
} // namespace Kasumi

#endif //KASUMI_GRID_H
