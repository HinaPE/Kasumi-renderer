#ifndef KASUMI_SCENE3_H
#define KASUMI_SCENE3_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/objects/cube.h"
#include "backends/objects/sphere.h"
#include "backends/objects/plane.h"
#include "backends/objects/cup.h"
#include "backends/api.h"

namespace Kasumi
{
class Scene3D final : public INSPECTOR, public VALID_CHECKER
{
public:
	void add(const ObjectMesh3DPtr &object);
	void remove(unsigned int id);
	void draw();
	void read_scene(const std::string &path = std::string(BackendsSceneDir) + "default.json");
	void export_scene(const std::string &path = std::string(BackendsSceneDir) + "default.json");
	Scene3D();

private:
	std::map<unsigned int, ObjectMesh3DPtr> _objects;
	ObjectParticles3DPtr _particles;
	ObjectGrid3DPtr _grid;
	int selected = 0;

private: // scene query
	struct SceneOpt
	{
		ObjectLines3DPtr _ray; // scene ray
		ObjectPoints3DPtr _ray_hit; // scene ray hit point
		HinaPE::Geom::SurfaceRayIntersection3 _ray_hit_info;
		bool _ray_enable = false;
		bool _line_enable = false;
		bool _point_enable = false;
	} _scene_opt;
	friend class Renderer3D;
	auto ray_cast(const mRay3 &ray) -> HinaPE::Geom::SurfaceRayIntersection3;

	void key(int key, int scancode, int action, int mods);
	void mouse_button(int button, int action, int mods);
	void mouse_scroll(double x_offset, double y_offset);
	void mouse_cursor(double x_pos, double y_pos);
	void INSPECT() final;
	void VALID_CHECK() const final;
};
using Scene3DPtr = std::shared_ptr<Scene3D>;
} // namespace Kasumi

#endif //KASUMI_SCENE3_H
