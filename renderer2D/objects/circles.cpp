#include "circles.h"

void Kasumi::Circles2DObject::_draw()
{
	if (_opt.dirty)
	{
		clear();
		std::vector<mVector2> pts;
		int d = 1;
		for (int i = 0; i <= 360; i += d)
			pts.emplace_back(_opt.position + _opt.radius * mVector2(std::sin(i * M_PI / 180.0f), std::cos(i * M_PI / 180.0f)));

		for (int i = 0; i < pts.size(); ++i)
			add(pts[i], pts[(i + 1) % pts.size()], _opt.color);
		_opt.dirty = false;
	}

	Lines2DObject::_draw();
}
