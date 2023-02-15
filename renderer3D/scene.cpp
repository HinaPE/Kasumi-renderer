#include "scene.h"
void Kasumi::Scene3D::draw()
{
	for (auto &object: _objects)
		if (is_renderable(object.second.get()))
			as_renderable(object.second.get())->render();
}
void Kasumi::Scene3D::add(const Kasumi::Object3DPtr &object) { _objects[object->ID] = object; }
void Kasumi::Scene3D::remove(unsigned int id)
{
	auto it = _objects.find(id);
	if (it != _objects.end())
		_objects.erase(it);
}
