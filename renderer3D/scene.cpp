#include "scene.h"
void Kasumi::Scene::draw()
{
	for (auto &object: _objects)
		if (is_renderable(object.second.get()))
			as_renderable(object.second.get())->render();
}
void Kasumi::Scene::add(const Kasumi::Object3DPtr &object) { _objects[object->ID] = object; }
void Kasumi::Scene::remove(unsigned int id)
{
	auto it = _objects.find(id);
	if (it != _objects.end())
		_objects.erase(it);
}
