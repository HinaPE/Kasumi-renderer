#include "scene_object.h"

Kasumi::SceneObject::SceneObject(Kasumi::ModelPtr &ptr)
{
	for (int i = 0; i < ptr->mesh_size(); ++i)
		for (auto &v: ptr->vertices(i))
			v.position -= ptr->center_of_gravity();
	_underlying = ptr;
}
Kasumi::SceneObject::SceneObject(Kasumi::ModelPtr &&ptr)
{
	for (int i = 0; i < ptr->mesh_size(); ++i)
		for (auto &v: ptr->vertices(i))
			v.position -= ptr->center_of_gravity();
	_underlying = std::move(ptr);
}
void Kasumi::SceneObject::render() { std::visit([&](auto &renderable) { renderable->render(); }, _underlying); }
void Kasumi::SceneObject::use_custom_shader(const ShaderPtr &shader) { std::visit([&](auto &renderable) { renderable->use_custom_shader(shader); }, _underlying); }
void Kasumi::SceneObject::update_mvp(const mMatrix4x4 &view, const mMatrix4x4 &projection)
{
	std::visit([&](auto &renderable)
			   {
				   auto model = _pose.get_model_matrix();
				   renderable->update_mvp(model, view, projection);
			   }, _underlying);
}
