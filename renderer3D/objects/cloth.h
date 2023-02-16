#ifndef KASUMI_CLOTH_H
#define KASUMI_CLOTH_H

#include "object3D.h"

namespace Kasumi
{
class ClothObject final : public ObjectMesh3D
{
public:
	struct Opt
	{
	} _opt;
	ClothObject() { ObjectMesh3D::_opt.mesh_name = "cloth"; }
	void sync_opt() final
	{
		if (!Object3D::_opt.dirty)
			return;

		ObjectMesh3D::sync_opt();
	}
};
using ClothObjectPtr = std::shared_ptr<ClothObject>;
} // namespace Kasumi

#endif //KASUMI_CLOTH_H
