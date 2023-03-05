#ifndef KASUMI_SCENE3_H
#define KASUMI_SCENE3_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "objects/cube.h"
#include "objects/sphere.h"
#include "objects/cup.h"
#include "objects/particles.h"
#include "objects/points.h"
#include "objects/lines.h"
#include "objects/grid.h"
#include "objects/plane.h"

#include "backends/api.h"

namespace Kasumi
{
class Scene3D final : public VALID_CHECKER, public INSPECTOR
{
public:
	void add(const Object3DPtr &object);
	void remove(unsigned int id);
	void draw();
	Scene3D();

public:
	void key(int key, int scancode, int action, int mods);
	void mouse_button(int button, int action, int mods);
	void mouse_scroll(double x_offset, double y_offset);
	void mouse_cursor(double x_pos, double y_pos);

	void INSPECT() final;
	void VALID_CHECK() const final;

private:
	std::map<unsigned int, Object3DPtr> _objects;
	int selected = 0;


private: // scene query
	auto ray_cast(const mRay3 &ray) -> HinaPE::Geom::SurfaceRayIntersection3;
	LinesObjectPtr _ray; // scene ray
	PointsObjectPtr _ray_hit; // scene ray hit point
	HinaPE::Geom::SurfaceRayIntersection3 _ray_hit_info;
	bool _ray_enable = false;
};
using Scene3DPtr = std::shared_ptr<Scene3D>;
} // namespace Kasumi

#endif //KASUMI_SCENE3_H
