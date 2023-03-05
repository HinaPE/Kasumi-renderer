#include "points.h"

std::shared_ptr<Kasumi::PointsObject> Kasumi::PointsObject::DefaultPoints = nullptr;
Kasumi::PointsObject::PointsObject()
{
	NAME = "Points" + std::to_string(ID);
	_shader = Shader::DefaultPointShader;
	_points = std::make_shared<Points>();
}
void Kasumi::PointsObject::Init()
{
	DefaultPoints = std::make_shared<Kasumi::PointsObject>();
}
void Kasumi::PointsObject::add(const mVector3 &point, const mVector3 &color)
{
	_points->add(point, color);
}
void Kasumi::PointsObject::clear()
{
	_points->clear();
}
void Kasumi::PointsObject::_draw()
{
	if (_points == nullptr)
		return;

	_points->render(*_shader);
}
void Kasumi::PointsObject::_update_uniform()
{
	Renderable::_update_uniform();
	_shader->uniform("model", POSE.get_model_matrix());
}
