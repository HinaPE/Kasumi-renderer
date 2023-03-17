#include "curve.h"

Kasumi::Curve2DObject::Curve2DObject()
{
	NAME = "Curve";
	_type = ObjectType::Line;
}
void Kasumi::Curve2DObject::set_function(const std::function<real(real)> &f, real x_min, real x_max)
{
	// TODO: NOT COMPLETE

	_vertices.clear();
	_indices.clear();

	real scale_x = 100;
	real scale_y = 100;

	auto now = x_min;
	auto idx = 0;
	while (now < x_max)
	{
		Vertex v;
		v.position = mVector2{scale_x * now, scale_y * f(now)};
		_vertices.push_back(v);
		_indices.push_back(idx++);
		now += 1;
	}

	_dirty = true;
}
