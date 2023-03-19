#ifndef HINAPE_VOLUME_RENDERER_H
#define HINAPE_VOLUME_RENDERER_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/api.h"

namespace Kasumi
{
class VolumeRenderer final : public App
{
public:
	VolumeRenderer();

protected:
	void prepare() final;
	void update(double dt) final;
};
} // namespace Kasumi

#endif //HINAPE_VOLUME_RENDERER_H
