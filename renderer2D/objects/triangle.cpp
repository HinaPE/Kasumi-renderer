#include "triangle.h"
void Kasumi::Triangle2DObject::_draw()
{
	if (_opt.dirty)
	{
		clear();
		add(_opt.p1, _opt.p2, _opt.color);
		add(_opt.p2, _opt.p3, _opt.color);
		add(_opt.p3, _opt.p1, _opt.color);
		_opt.dirty = false;
	}

	Lines2DObject::_draw();
}
