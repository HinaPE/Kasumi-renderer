#ifndef KASUMI_OBJECT3D_H
#define KASUMI_OBJECT3D_H

#include "mesh.h"
#include "pose.h"
#include "api.h"

namespace Kasumi
{
class Object3D : public Inspector
{
public:
	unsigned int ID;
	Object3D();

protected:
	void _inspect() override;
	Pose _pose;
};
using Object3DPtr = std::shared_ptr<Object3D>;

class ObjectMesh3D final : public Object3D, public Renderable
{
public:
	friend class Renderer3D;

protected:
	void _draw() final;
	void _inspect() final;

private:
	UniversalMeshPtr _mesh;
};
using ObjectMesh3DPtr = std::shared_ptr<ObjectMesh3D>;

} // namespace Kasumi
#endif //KASUMI_OBJECT3D_H
