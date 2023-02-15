#include "scene.h"
void Kasumi::Scene3D::draw()
{
	for (auto &pair: _objects)
		if (is_renderable(pair.second.get()))
			as_renderable(pair.second.get())->render();
}
void Kasumi::Scene3D::add(const Kasumi::Object3DPtr &object)
{
	if (is_renderable(object.get()))
	{
		as_renderable(object.get())->_shader = Shader::DefaultMeshShader;
		as_renderable(object.get())->_get_model = [this, &object]() -> mMatrix4x4 { return object->_opt.pose.get_model_matrix(); };
		as_renderable(object.get())->_get_view = [this]() -> mMatrix4x4 { return _camera->get_view(); };
		as_renderable(object.get())->_get_projection = [this]() -> mMatrix4x4 { return _camera->get_projection(); };
	}
	_objects[object->ID] = object;
}
void Kasumi::Scene3D::remove(unsigned int id)
{
	auto it = _objects.find(id);
	if (it != _objects.end())
		_objects.erase(it);
}
