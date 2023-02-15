#ifndef KASUMI_TRIANGLE_H
#define KASUMI_TRIANGLE_H

#include "lines.h"

namespace Kasumi
{
class Triangle2DObject : public Lines2DObject
{
public:
	struct Opt
	{
		mVector2 p1, p2, p3;
		mVector3 color;
	} _opt;

protected:
	void _draw() override;
	bool _dirty = true;
};
} // namespace Kasumi

#endif //KASUMI_TRIANGLE_H
