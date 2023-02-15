#include "scene.h"
void Kasumi::Scene3D::draw()
{
	for (auto &pair: _objects)
		if (is_renderable(pair.second.get()))
			as_renderable(pair.second.get())->render();
}
void Kasumi::Scene3D::add(const Kasumi::Object3DPtr &object) { _objects[object->ID] = object; }
void Kasumi::Scene3D::remove(unsigned int id)
{
	auto it = _objects.find(id);
	if (it != _objects.end())
		_objects.erase(it);
}
void Kasumi::Scene3D::VALID_CHECK() const
{
	for (auto &pair: _objects)
		if (need_valid_check(pair.second.get()))
			as_valid_check(pair.second.get())->VALID_CHECK();
}
void Kasumi::Scene3D::INSPECT()
{
	ImGui::Text("Scene Info");
	for (auto &pair: _objects)
	{
		ImGui::RadioButton(std::to_string(pair.first).c_str(), &selected, static_cast<int>(pair.first));
	}
	auto &obj = _objects[selected];
	obj->INSPECT();
}
