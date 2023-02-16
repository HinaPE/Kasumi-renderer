#ifndef KASUMI_CIRCLES_H
#define KASUMI_CIRCLES_H

#include "lines.h"

namespace Kasumi
{
class Circles2DObject : public Lines2DObject
{
public:
	struct Opt
	{
		bool dirty = true;
		mVector2 position;
		real radius;
		mVector3 color = HinaPE::Color::PINK;
	} _opt;

protected:
	void _draw() override;
};
using Circles2DObjectPtr = std::shared_ptr<Circles2DObject>;
} // namespace Kasumi

#endif //KASUMI_CIRCLES_H
