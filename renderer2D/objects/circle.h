#ifndef KASUMI_CIRCLE_H
#define KASUMI_CIRCLE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object2D.h"

namespace Kasumi
{
class Circle2DObject : public Object2D
{
public:
	real _radius = 100;
	Circle2DObject();
};
using Circle2DObjectPtr = std::shared_ptr<Circle2DObject>;
} // namespace Kasumi

#endif //KASUMI_CIRCLE_H
