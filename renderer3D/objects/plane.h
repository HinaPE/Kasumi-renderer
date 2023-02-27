#ifndef KASUMI_PLANE_H
#define KASUMI_PLANE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"
#include "geom/surface3.h"
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
	PlaneObject() { ObjectMesh3D::_opt.mesh_name = "plane"; }
	void _rebuild_() final;
	void INSPECT() override;
};
} // namespace Kasumi

#endif //KASUMI_PLANE_H
