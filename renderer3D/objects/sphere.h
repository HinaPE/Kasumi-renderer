#ifndef KASUMI_SPHERE_H
#define KASUMI_SPHERE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"

namespace Kasumi
{
class SphereObject final : public ObjectMesh3D
{
public:
	struct Opt
	{
		real radius = 1;
	} _opt;
	SphereObject();
	void sync_opt() final;
};
using SphereObjectPtr = std::shared_ptr<SphereObject>;
} // namespace Kasumi

#endif //KASUMI_SPHERE_H
