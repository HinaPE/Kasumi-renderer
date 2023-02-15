#ifndef HINAPE_SCENE_H
#define HINAPE_SCENE_H

#include "object3D.h"
#include "camera.h"

namespace Kasumi
{
class Scene3D : public VALID_CHECKER
{
public:
	void add(const Object3DPtr& object);
	void remove(unsigned int id);
	void draw();

private:
	std::map<unsigned int, Object3DPtr> _objects; // mesh / light
	CameraPtr _camera;
};
} // namespace Kasumi

#endif //HINAPE_SCENE_H
