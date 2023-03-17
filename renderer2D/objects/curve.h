#ifndef HINAPE_CURVE_H
#define HINAPE_CURVE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object2D.h"

namespace Kasumi
{
class Curve2DObject : public Object2D
{
public:
	Curve2DObject();
	void set_function(const std::function<real(real)> &f, real x_min = -100, real x_max = 1000);
};
using Curve2DObjectPtr = std::shared_ptr<Curve2DObject>;
} // namespace Kasumi

#endif //HINAPE_CURVE_H
