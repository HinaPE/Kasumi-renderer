#include "rectangle.h"
Kasumi::Rectangle2DObject::Rectangle2DObject()
{
	NAME = "Rectangle";

	_vertices.clear();
	_indices.clear();

	Vertex v1, v2, v3, v4;
	v1.position = mVector2{-_width / 2, -_height / 2};
	v2.position = mVector2{_width / 2, -_height / 2};
	v3.position = mVector2{_width / 2, _height / 2};
	v4.position = mVector2{-_width / 2, _height / 2};

	_vertices.push_back(v1);
	_vertices.push_back(v2);
	_vertices.push_back(v3);
	_vertices.push_back(v4);

	_indices.push_back(0);
	_indices.push_back(1);
	_indices.push_back(2);
	_indices.push_back(0);
	_indices.push_back(2);
	_indices.push_back(3);

	_dirty = true;
}
