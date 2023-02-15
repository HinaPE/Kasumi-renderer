#ifndef HINAPE_SCENE_H
#define HINAPE_SCENE_H

#include "objects/cube.h"
#include "objects/sphere.h"
#include "objects/particles.h"
#include "camera.h"

namespace Kasumi
{
class Scene3D : public VALID_CHECKER, public INSPECTOR
{
public:
	void add(const Object3DPtr& object);
	void remove(unsigned int id);
	void draw();

	void VALID_CHECK() const final;
	void INSPECT() final;

private:
	std::map<unsigned int, Object3DPtr> _objects; // mesh, light
	int selected = 0;
};
using Scene3DPtr = std::shared_ptr<Scene3D>;
} // namespace Kasumi

#endif //HINAPE_SCENE_H
