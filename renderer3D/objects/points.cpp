#include "points.h"

std::shared_ptr<Kasumi::PointsObject> Kasumi::PointsObject::DefaultPoints = nullptr;
void Kasumi::PointsObject::Init()
{
	DefaultPoints = std::make_shared<Kasumi::PointsObject>();
	DefaultPoints->_rebuild_();
}
void Kasumi::PointsObject::add(const mVector3 &point, const mVector3 &color)
{
	_points->add(point, color);
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
	_shader->uniform("model", Object3D::_opt.pose.get_model_matrix());
}
