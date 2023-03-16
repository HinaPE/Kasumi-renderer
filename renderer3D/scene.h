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
	void add(const ObjectParticles3DPtr &object);
	void add(const ObjectLines3DPtr &object);
	void add(const ObjectLines3DInstancedPtr &object);
	void add(const ObjectPoints3DPtr &object);
	void add(const ObjectPoints3DInstancedPtr &object);
	void add(const ObjectGrid3DPtr &object);
	void remove(unsigned int id);
	void draw();
	void read_scene(const std::string &path = std::string(BackendsSceneDir) + "default.json"); // NOT IMPLEMENTED
	void export_scene(const std::string &path = std::string(BackendsSceneDir) + "default.json"); // NOT IMPLEMENTED
	Scene3D();

private:
	std::map<unsigned int, ObjectMesh3DPtr> _objects;
	std::map<unsigned int, ObjectParticles3DPtr> _particle_objects;
	std::map<unsigned int, ObjectGrid3DPtr> _grid_objects;
	std::map<unsigned int, ObjectLines3DPtr> _line_objects;
	std::map<unsigned int, ObjectLines3DInstancedPtr> _line_instance_objects;
	std::map<unsigned int, ObjectPoints3DPtr> _point_objects;
	std::map<unsigned int, ObjectPoints3DInstancedPtr> _point_instance_objects;
	int _selected = 0;
	int _selected_particle = 0;

public:
	// scene query
	struct SceneOpt
	{
		// mouse ray cast
		ObjectLines3DPtr _ray; // scene ray
		ObjectPoints3DPtr _ray_hit; // scene ray hit point
		HinaPE::Geom::SurfaceRayIntersection3 _ray_hit_info;
		bool _ray_enable = false;
		bool _particle_mode = false;

		// support for line/point debugging
		bool _line_enable = false;
		bool _point_enable = false;

		// surface debugging
		mVector3 debug_point;
		ObjectPoints3DPtr debug_point_obj;
		bool inside = false;
	} _scene_opt;
	friend class Renderer3D;
	friend class VolumeRenderer;
	auto ray_cast(const mRay3 &ray) -> HinaPE::Geom::SurfaceRayIntersection3;

protected:
	void key(int key, int scancode, int action, int mods);
	void mouse_button(int button, int action, int mods);
	void mouse_cursor(double x_pos, double y_pos);
	void INSPECT() final;
	void VALID_CHECK() const final;
};
using Scene3DPtr = std::shared_ptr<Scene3D>;
} // namespace Kasumi

#endif //KASUMI_SCENE3_H
