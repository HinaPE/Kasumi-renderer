#ifndef HINAPE_SCENE_H
#define HINAPE_SCENE_H

#include "object3D.h"

namespace Kasumi
{
class Scene
{
public:
	void add(const Object3DPtr& object);
	void remove(unsigned int id);
	void draw();

private:
	std::map<unsigned int, Object3DPtr> _objects;
};
} // namespace Kasumi

#endif //HINAPE_SCENE_H
