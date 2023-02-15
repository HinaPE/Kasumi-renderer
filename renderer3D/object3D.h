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
	static unsigned int ID_GLOBAL;
	const unsigned int ID;
	struct Opt
	{
		bool dirty = true;
		Pose pose;
	} _opt;
	Object3D() : ID(ID_GLOBAL++) {}
	virtual void sync_opt() {}

protected:
	// inspector
	void _inspect() override;
};
using Object3DPtr = std::shared_ptr<Object3D>;

class ObjectMesh3D : public Object3D, public Renderable, public VALID_CHECKER
{
public:
	// opt & constructors
	struct Opt : public Object3D::Opt
	{
		std::string mesh_path = "cube";
		std::string texture_path; // Default: not
		mVector3 color = HinaPE::Color::RED;
	} _opt;
	ObjectMesh3D() = default;
	void sync_opt() override
	{
		if (_opt.dirty)
		{
			if (!_opt.texture_path.empty())
				_mesh = std::make_shared<UniversalMesh>(_opt.mesh_path, _opt.texture_path);
			else
				_mesh = std::make_shared<UniversalMesh>(_opt.mesh_path, _opt.color);
		}

		Object3D::sync_opt();
	}

protected:
	// renderable
	void _draw() final;
	auto _get_model() -> mMatrix4x4 final { return _opt.pose.get_model_matrix(); }
	// inspector
	void _inspect() override;
	// valid
	void VALID_CHECK() const override;
	// fields
	UniversalMeshPtr _mesh;
};
using ObjectMesh3DPtr = std::shared_ptr<ObjectMesh3D>;

class CubeObject final : public ObjectMesh3D
{
public:
	struct Opt : public ObjectMesh3D::Opt
	{
		real width = 1;
		real height = 1;
		real depth = 1;
	} _opt;
	CubeObject() = default;
	void sync_opt() final
	{
		_opt.mesh_path = std::string(BackendsModelDir) + "cube.obj";
		_opt.pose.scale.x() = _opt.width;
		_opt.pose.scale.y() = _opt.height;
		_opt.pose.scale.z() = _opt.depth;

		ObjectMesh3D::sync_opt();
	}

protected:
	void _inspect() override;

private:
	HinaPE::Geom::Box3 _cube; // NOT USED YET
};
using CubeObjectPtr = std::shared_ptr<CubeObject>;
} // namespace Kasumi
#endif //KASUMI_OBJECT3D_H
