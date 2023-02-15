#ifndef KASUMI_TRIANGLE_H
#define KASUMI_TRIANGLE_H

#include "object2D.h"
namespace Kasumi
{
class Triangle2D : public Object2D
{
	struct Opt
	{
		mVector2 p1, p2, p3;
	} _opt;
};
} // namespace Kasumi

#endif //KASUMI_TRIANGLE_H
