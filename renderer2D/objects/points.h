#ifndef KASUMI_POINTS_H
#define KASUMI_POINTS_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object2D.h"

namespace Kasumi
{
class Points2DObject final : public Object2D, public Renderable
{
public:
	struct Vertex
	{
		mVector2 position;
		mVector3 color;
	};
	Points2DObject();

	void add(const mVector2 &pt, const mVector3 &color = HinaPE::Color::PURPLE);

protected:
	void _draw() final;

private:
	unsigned int _vao, _vbo, _ebo;
	std::vector<Vertex> _points; // start, end
	bool _dirty = true;
};
using Points2DObjectPtr = std::shared_ptr<Points2DObject>;
} // namespace Kasumi

#endif //KASUMI_POINTS_H
