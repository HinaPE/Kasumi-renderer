#ifndef KASUMI_SCENE2_H
#define KASUMI_SCENE2_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "objects/circle.h"
#include "objects/rectangle.h"

namespace Kasumi
{
class Scene2D
{
public:
	void add(const Object2DPtr& object);
	void remove(unsigned int id);
	void draw();

private:
	std::map<unsigned int, Object2DPtr> _objects;
	int selected = 0;
};
using Scene2DPtr = std::shared_ptr<Scene2D>;
} // namespace Kasumi

#endif //KASUMI_SCENE2_H
