#ifndef HINAPE_VOLUME_RENDERER_H
#define HINAPE_VOLUME_RENDERER_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "common.h"

namespace Kasumi
{
struct Frame
{
	Frame(real width, real height, int cols, int rows) : _width(width), _height(height), _rows(rows), _cols(cols)
	{
		_frame.resize(rows * cols);
		_view_point = mVector3(0.0f, 0.0f, 0.0f);
	}
	auto operator()(int x, int y) -> mVector3 & { return _frame[y * _cols + x]; }
	auto operator()(int x, int y) const -> const mVector3 & { return _frame[y * _cols + x]; }
	auto ray(int x, int y) const -> mRay3
	{
		real u = (static_cast<real>(x) + 0.5f) / static_cast<real>(_cols);
		real v = (static_cast<real>(y) + 0.5f) / static_cast<real>(_rows);
		real x_ = u * _width - _width / 2.0f;
		real y_ = v * _height - _height / 2.0f;
		return {_view_point, mVector3(x_, y_, -1.0f)};
	}
	void fill_each_ray(const std::function<mVector3(const mRay3 &)> &func)
	{
		HinaPE::Util::parallelFor(HinaPE::Constant::ZeroSize, _frame.size(), [&](int i)
		{
			int x = i % _cols;
			int y = i / _cols;
			(*this)(x, y) = func(ray(x, y));
		}, HinaPE::Util::ExecutionPolicy::Serial);
	}
	void write_to_file(const std::string &filename) const
	{
		std::ofstream ofs(filename, std::ios::binary);
		ofs << "P3" << std::endl;
		ofs << _cols << " " << _rows << std::endl;
		ofs << "255" << std::endl;
		for (const auto &color: _frame)
		{
			ofs << static_cast<int>(color.x() * 255.0f) << " "
				<< static_cast<int>(color.y() * 255.0f) << " "
				<< static_cast<int>(color.z() * 255.0f) << std::endl;
		}
	}

	std::vector<mVector3> _frame;
	real _width, _height;
	int _rows, _cols;
	mVector3 _view_point;
};

class VolumeRenderer final
{
public:
	VolumeRenderer();
	void render();

private:
	std::shared_ptr<Frame> _frame;
};
} // namespace Kasumi

#endif //HINAPE_VOLUME_RENDERER_H
