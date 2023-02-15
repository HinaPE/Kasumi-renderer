#include "triangle.h"
void Kasumi::Triangle2DObject::_draw()
{
	if (_dirty)
	{
		clear();
		add(_opt.p1, _opt.p2);
		add(_opt.p2, _opt.p3);
		add(_opt.p3, _opt.p1);
	}

	Lines2DObject::_draw();
}
