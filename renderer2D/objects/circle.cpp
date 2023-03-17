#include "circle.h"

Kasumi::Circle2DObject::Circle2DObject()
{
	NAME = "Circle";

	_vertices.clear();
	_indices.clear();

	size_t segment = 100;

	for (size_t i = 0; i < segment; ++i)
	{
		Vertex v;
		real theta = 2 * HinaPE::Constant::PI * static_cast<real>(i) / static_cast<real>(segment);
		v.position = _radius * mVector2{std::cos(-theta), std::sin(-theta)};
		_vertices.push_back(v);
	}
	Vertex v0;
	v0.position = mVector2::Zero();
	_vertices.push_back(v0);

	for (size_t i = 0; i < segment; ++i)
	{
		_indices.push_back(i);
		_indices.push_back((i + 1) % segment);
		_indices.push_back(segment); // v0
	}

	_dirty = true;
}
