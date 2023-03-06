#ifndef KASUMI_OBJECT3D_H
#define KASUMI_OBJECT3D_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/api.h"
#include "geom/collider3.h"
#include "geom/surface3.h"

namespace Kasumi
{
// @formatter:off
class ObjectMesh3D :
		public Renderable,
		public IDBase,
		public NameBase,
		public PoseBase,
		public VALID_CHECKER
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

protected:
	std::string MESH = "cube";
	std::string TEXTURE; // Default: not
	mVector3 COLOR = HinaPE::Color::CYAN;

	MeshPtr _mesh;
	HinaPE::Geom::RigidBodyCollider3Ptr _collider;

	void INSPECT() override;
	void VALID_CHECK() const override;
};
using ObjectMesh3DPtr = std::shared_ptr<ObjectMesh3D>;
// @formatter:on

class ObjectLines3D :
		public Renderable,
		public IDBase,
		public NameBase,
		public PoseBase,
		public VALID_CHECKER
{
public:
	static void Init();
	static std::shared_ptr<ObjectLines3D> DefaultLines;

	void add(const mVector3 &start, const mVector3 &end, const mVector3 &color = HinaPE::Color::PURPLE);
	void clear();
	ObjectLines3D();

protected:
	void _draw() final;
	void _update_uniform() final;

private:
	LinesPtr _lines;
};
using ObjectLines3DPtr = std::shared_ptr<ObjectLines3D>;

class ObjectPoints3D :
		public Renderable,
		public IDBase,
		public NameBase,
		public PoseBase,
		public VALID_CHECKER
{
public:
	static void Init();
	static std::shared_ptr<ObjectPoints3D> DefaultPoints;
	ObjectPoints3D();

	void add(const mVector3 &point, const mVector3 &color = HinaPE::Color::PURPLE);
	void clear();

protected:
	void _draw() final;
	void _update_uniform() final;

private:
	PointsPtr _points;
};
using ObjectPoints3DPtr = std::shared_ptr<ObjectPoints3D>;
} // namespace Kasumi
#endif //KASUMI_OBJECT3D_H
