#include "scene.h"

void Kasumi::Scene2D::add(const Kasumi::Object2DPtr &object) { _objects[object->ID] = object; }
void Kasumi::Scene2D::remove(unsigned int id)
{
	auto it = _objects.find(id);
	if (it != _objects.end())
		_objects.erase(it);
}
void Kasumi::Scene2D::draw()
{
	for (auto &pair: _objects)
	{
		pair.second->_shader->uniform("iResolution", mVector2(1024, 768));
		pair.second->render();
	}
}
