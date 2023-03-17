#ifndef HINAPE_FUNCTION_VIEWER2D_H
#define HINAPE_FUNCTION_VIEWER2D_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/api.h"

namespace Kasumi
{
class FunctionViewer2D final : public App
{
public:
	FunctionViewer2D();
	void load(const std::function<real(real)> &f, real x_min, real x_max);
};
} // namespace Kasumi

#endif //HINAPE_FUNCTION_VIEWER2D_H
