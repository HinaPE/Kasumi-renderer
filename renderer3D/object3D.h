#ifndef KASUMI_OBJECT3D_H
#define KASUMI_OBJECT3D_H

#include "mesh.h"
#include "pose.h"
#include "inspector.h"

namespace Kasumi
{
class Object3D final : protected Inspector
{
public:
	friend class Renderer3D;

protected:
	void inspect() final;

private:
	UniversalMeshPtr _mesh;
	Pose _pose;
};
} // namespace Kasumi
#endif //KASUMI_OBJECT3D_H
