#include "lines.h"

std::shared_ptr<Kasumi::LinesObject> Kasumi::LinesObject::DefaultLines = nullptr;
void Kasumi::LinesObject::Init()
{
	DefaultLines = std::make_shared<Kasumi::LinesObject>();
	DefaultLines->sync_opt();
}
void Kasumi::LinesObject::add(const mVector3 &start, const mVector3 &end, const mVector3 &color)
{
	_lines->add(start, end, color);
}
void Kasumi::LinesObject::_draw()
{
	if (_lines == nullptr)
		return;

	_lines->render(*_shader);
}
void Kasumi::LinesObject::_update_uniform()
{
	Renderable::_update_uniform();
	_shader->uniform("model", Object3D::_opt.pose.get_model_matrix());
}
