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
	// opt & constructors
	const unsigned int ID;
	struct Opt
	{
		bool dirty = false;
		Pose pose;
	} _opt;
	explicit Object3D(const Opt &opt);

protected:
	// inspector
	void _inspect() override;
};
using Object3DPtr = std::shared_ptr<Object3D>;

class ObjectMesh3D : public Object3D, public Renderable
{
public:
	// opt & constructors
	struct Opt : public Object3D::Opt
	{

	} _opt;
	explicit ObjectMesh3D(const Opt &opt);

protected:
	// renderable
	void _draw() final;

	// inspector
	void _inspect() final;

private:
	UniversalMeshPtr _mesh;
};
using ObjectMesh3DPtr = std::shared_ptr<ObjectMesh3D>;

class CubeObject : public ObjectMesh3D
{
public:
	struct Opt : public ObjectMesh3D::Opt
	{
		real width = 1;
		real height = 1;
		real depth = 1;
	} _opt;
	explicit CubeObject(const Opt &opt);

private:
	HinaPE::Geom::Box3 _cube;
};
using CubeObjectPtr = std::shared_ptr<CubeObject>;
} // namespace Kasumi
#endif //KASUMI_OBJECT3D_H
