#ifndef KASUMI_PLANE_H
#define KASUMI_PLANE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"
namespace Kasumi
{
class PlaneObject : public ObjectMesh3D, public HinaPE::Geom::Plane3
{
public:
	PlaneObject();
	void sync_opt() final {}
};
} // namespace Kasumi

#endif //KASUMI_PLANE_H
