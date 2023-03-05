#ifndef KASUMI_OBJECT3D_H
#define KASUMI_OBJECT3D_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/api.h"
#include "geom/collider3.h"
#include "geom/surface3.h"

namespace Kasumi
{
class Object3D : public INSPECTOR
{
public:
	Object3D() : ID(ID_GLOBAL++) {}

	void INSPECT() override;

public:
	static unsigned int ID_GLOBAL;
	const unsigned int ID;
	std::string NAME = "Untitled";
	Pose POSE;
	bool _dirty{false};
};
using Object3DPtr = std::shared_ptr<Object3D>;

// @formatter:off
class ObjectMesh3D : public Object3D, public Renderable, public VALID_CHECKER
{
public:
	auto ray_cast(const mRay3 & ray) const -> HinaPE::Geom::SurfaceRayIntersection3;

	virtual void sync_opt() = 0;

protected:
	virtual void _init() final;
	void _draw() final;
	void _update_uniform() final;

	friend class Scene3D;
	void _switch_surface() const { _mesh->_opt.dirty = true;_mesh->_opt.render_surface = !_mesh->_opt.render_surface; }
	void _switch_wireframe() const { _mesh->_opt.dirty = true;_mesh->_opt.render_wireframe = !_mesh->_opt.render_wireframe; }
	void _switch_bbox() const { _mesh->_opt.dirty = true;_mesh->_opt.render_bbox = !_mesh->_opt.render_bbox; }

	void INSPECT() override;
	void VALID_CHECK() const override;

	MeshPtr _mesh;
	HinaPE::Geom::RigidBodyCollider3Ptr _collider;

protected:
	std::string MESH = "cube";
	std::string TEXTURE; // Default: not
	mVector3 COLOR = HinaPE::Color::CYAN;
};
using ObjectMesh3DPtr = std::shared_ptr<ObjectMesh3D>;
// @formatter:on
} // namespace Kasumi
#endif //KASUMI_OBJECT3D_H
