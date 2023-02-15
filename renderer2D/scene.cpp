#include "scene.h"

void Kasumi::Scene2D::add(const Kasumi::Object2DPtr &object){ _objects[object->ID] = object; }
void Kasumi::Scene2D::remove(unsigned int id)
{
	auto it = _objects.find(id);
	if (it != _objects.end())
		_objects.erase(it);
}
void Kasumi::Scene2D::draw()
{
	for (auto &pair: _objects)
		if (is_renderable(pair.second.get()))
			as_renderable(pair.second.get())->render();
}
void Kasumi::Scene2D::VALID_CHECK() const
{
	VALID_CHECKER::VALID_CHECK();
}
void Kasumi::Scene2D::INSPECT()
{
	for (auto &pair: _objects)
		if (need_valid_check(pair.second.get()))
			as_valid_check(pair.second.get())->VALID_CHECK();
}
