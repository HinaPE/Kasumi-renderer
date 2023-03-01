#ifndef KASUMI_PLANE_H
#define KASUMI_PLANE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"
namespace Kasumi
{
class PlaneObject : public ObjectMesh3D
{
public:
	struct Opt
	{
		real width = 1;
		real height = 1;
	} _opt;
	PlaneObject();
	void sync_opt() final {}
	void INSPECT() override;
};
} // namespace Kasumi

#endif //KASUMI_PLANE_H
