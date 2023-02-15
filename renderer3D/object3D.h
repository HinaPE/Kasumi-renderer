#ifndef KASUMI_OBJECT3D_H
#define KASUMI_OBJECT3D_H

#include "mesh.h"
#include "pose.h"
#include "api.h"

namespace Kasumi
{
class Object : public Inspector
{
protected:
	void inspect() override;
	Pose _pose;
	unsigned int ID;
};
class ObjectMesh3D final : public Object, public Renderable
{
public:
	friend class Renderer3D;

protected:
	void inspect() final;

private:
	UniversalMeshPtr _mesh;
};
} // namespace Kasumi
#endif //KASUMI_OBJECT3D_H
