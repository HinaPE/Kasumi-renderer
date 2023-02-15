#ifndef HINAPE_LINES2D_H
#define HINAPE_LINES2D_H

#include "object2D.h"

namespace Kasumi
{
class Lines2DObject : public Object2D, public Renderable
{
public:
	static void Init();
	static std::shared_ptr<Lines2DObject> Default2DLines;

	void add(const mVector2 &start, const mVector2 &end, const mVector3 &color = HinaPE::Color::PURPLE);
	void clear();

public:
	struct Vertex
	{
		mVector2 position;
		mVector3 color;
	};
	Lines2DObject();

protected:
	void _draw() override;

private:
	unsigned int _vao, _vbo, _ebo;
	std::vector<Vertex> _lines; // start, end
	bool _dirty = true;
};
using Lines2DObjectPtr = std::shared_ptr<Lines2DObject>;
} // namespace Kasumi

#endif //HINAPE_LINES2D_H
