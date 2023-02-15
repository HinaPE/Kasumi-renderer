#ifndef KASUMI_SPHERE_H
#define KASUMI_SPHERE_H

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
	SphereObject() { ObjectMesh3D::_opt.mesh_name = "sphere"; }
	void sync_opt() final
	{
		Object3D::_opt.pose.scale.x() = _opt.radius;
		Object3D::_opt.pose.scale.y() = _opt.radius;
		Object3D::_opt.pose.scale.z() = _opt.radius;
		Object3D::_opt.dirty = true;

		ObjectMesh3D::sync_opt();
	}
};
using SphereObjectPtr = std::shared_ptr<SphereObject>;
} // namespace Kasumi
#endif //KASUMI_SPHERE_H
