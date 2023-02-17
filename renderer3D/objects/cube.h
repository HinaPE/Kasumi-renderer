#ifndef KASUMI_CUBE_H
#define KASUMI_CUBE_H

#include "object3D.h"
namespace Kasumi
{
class CubeObject final : public ObjectMesh3D
{
public:
	struct Opt
	{
		real width = 1;
		real height = 1;
		real depth = 1;
	} _opt;
	CubeObject() { ObjectMesh3D::_opt.mesh_name = "cube"; }
	void _rebuild_() final
	{
		if (!Object3D::_opt.dirty)
			return;

		Object3D::_opt.pose.scale.x() = _opt.width;
		Object3D::_opt.pose.scale.y() = _opt.height;
		Object3D::_opt.pose.scale.z() = _opt.depth;

		ObjectMesh3D::_rebuild_();
	}
	void INSPECT() final;

private:
	HinaPE::Geom::Box3 _cube; // NOT USED YET
};
using CubeObjectPtr = std::shared_ptr<CubeObject>;

} // namespace Kasumi

#endif //KASUMI_CUBE_H
