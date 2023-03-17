#ifndef HINAPE_RECTANGLE_H
#define HINAPE_RECTANGLE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object2D.h"

namespace Kasumi
{
class Rectangle2DObject : public Object2D
{
public:
	real _width = 200;
	real _height = 200;
	Rectangle2DObject();
};
using Rectangle2DObjectPtr = std::shared_ptr<Rectangle2DObject>;
} // namespace Kasumi

#endif //HINAPE_RECTANGLE_H
