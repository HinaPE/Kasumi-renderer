#ifndef KASUMI_LIGHT_H
#define KASUMI_LIGHT_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"

namespace Kasumi
{
class DirectLightObject : public ObjectMesh3D
{
public:
	struct Opt
	{
		mVector3 origin;
		mVector3 direction;
	} _opt;
	DirectLightObject() { ObjectMesh3D::_opt.mesh_name = "arrow"; }
	void _rebuild_() final
	{
		if (!Object3D::_opt.dirty)
			return;

		Object3D::_opt.pose.position = _opt.origin;
		Object3D::_opt.pose.euler = mQuaternion(mVector3(0, 0, 1), _opt.direction).euler();

		ObjectMesh3D::_rebuild_();
	}
	void INSPECT() final;
};
} // namespace Kasumi

#endif //KASUMI_LIGHT_H
