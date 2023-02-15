#ifndef KASUMI_OBJECT3D_H
#define KASUMI_OBJECT3D_H

#include "mesh.h"
#include "pose.h"
#include "api.h"

namespace Kasumi
{
class Object3D : public INSPECTOR
{
public:
	// opt & constructors
	static unsigned int ID_GLOBAL;
	const unsigned int ID;
	struct Opt
	{
		bool dirty = true;
		Pose pose;
	} _opt;
	Object3D() : ID(ID_GLOBAL++) {}
	virtual void sync_opt() { _opt.dirty = false; }

	void INSPECT() override;
};
using Object3DPtr = std::shared_ptr<Object3D>;

class ObjectMesh3D : public Object3D, public Renderable, public VALID_CHECKER
{
public:
	// opt & constructors
	struct Opt
	{
		std::string mesh_name = "cube";
		std::string texture_path; // Default: not
		mVector3 color = HinaPE::Color::RED;
	} _opt;
	ObjectMesh3D() = default;
	void sync_opt() override
	{
		if (!Object3D::_opt.dirty)
			return;

		if (!_opt.texture_path.empty())
			_mesh = std::make_shared<UniversalMesh>(_opt.mesh_name, _opt.texture_path);
		else
			_mesh = std::make_shared<UniversalMesh>(_opt.mesh_name, _opt.color);

		Object3D::sync_opt();
	}

protected:
	void _draw() final;
	auto _get_model() -> mMatrix4x4 final { return Object3D::_opt.pose.get_model_matrix(); }
	void INSPECT() override;
	void VALID_CHECK() const override;

	UniversalMeshPtr _mesh;
};
using ObjectMesh3DPtr = std::shared_ptr<ObjectMesh3D>;

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
	void sync_opt() final
	{
		if (!Object3D::_opt.dirty)
			return;

		Object3D::_opt.pose.scale.x() = _opt.width;
		Object3D::_opt.pose.scale.y() = _opt.height;
		Object3D::_opt.pose.scale.z() = _opt.depth;

		ObjectMesh3D::sync_opt();
	}
	void INSPECT() final;

private:
	HinaPE::Geom::Box3 _cube; // NOT USED YET
};
using CubeObjectPtr = std::shared_ptr<CubeObject>;

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
} // namespace Kasumi
#endif //KASUMI_OBJECT3D_H
