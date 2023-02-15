#ifndef HINAPE_POINTS_H
#define HINAPE_POINTS_H

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

#endif //HINAPE_POINTS_H
