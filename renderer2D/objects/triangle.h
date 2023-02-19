#ifndef KASUMI_TRIANGLE_H
#define KASUMI_TRIANGLE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "lines.h"

namespace Kasumi
{
class Triangle2DObject : public Lines2DObject
{
public:
	struct Opt
	{
		bool dirty = true;
		mVector2 p1, p2, p3;
		mVector3 color = HinaPE::Color::PURPLE;
	} _opt;

protected:
	void _draw() override;
};
using Triangle2DObjectPtr = std::shared_ptr<Triangle2DObject>;
} // namespace Kasumi

#endif //KASUMI_TRIANGLE_H
