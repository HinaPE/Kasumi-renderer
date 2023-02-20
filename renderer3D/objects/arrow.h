#ifndef HINAPE_ARROW_H
#define HINAPE_ARROW_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"

namespace Kasumi
{
class ArrowObject : public ObjectMesh3D
{
public:
	struct Opt
	{
		mVector3 origin = mVector3::Zero();
		mVector3 direction = mVector3::UnitZ();
	} _opt;
	ArrowObject() { ObjectMesh3D::_opt.mesh_name = "arrow"; }
	void _rebuild_() final
	{
		if (!Object3D::_opt.dirty)
			return;

		Object3D::_opt.pose.position = _opt.origin;
		Object3D::_opt.pose.euler = mQuaternion(mVector3(0, 0, 1), _opt.direction).euler();
		Object3D::_opt.pose.scale = mVector3(0.2, 0.5, 0.2);

		ObjectMesh3D::_rebuild_();
	}
	void INSPECT() override;
};
using ArrowObjectPtr = std::shared_ptr<ArrowObject>;
} // namespace Kasumi

#endif //HINAPE_ARROW_H
