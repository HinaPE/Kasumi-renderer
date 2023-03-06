//#include "grid.h"
//
//Kasumi::GridObject::GridObject()
//{
//	NAME = "Grid";
//	_shader = Shader::DefaultInstanceLineShader;
//}
//void Kasumi::GridObject::init(const HinaPE::Geom::Grid3Ptr &grid)
//{
//	int scale = 15;
//	for (int i = -scale; i < scale; ++i)
//	{
//		for (int j = -scale; j < scale; ++j)
//		{
//			for (int k = -scale; k < scale; ++k)
//			{
//				Pose pose;
//				pose.position = 0.1 * mVector3(i, j, k);
//				_poses.push_back(pose);
//			}
//		}
//	}
//
//	std::shared_ptr<Lines> _bbox_lines = std::make_shared<Lines>();
//	_bbox_lines->clear();
//	auto l = mVector3{-HinaPE::Constant::Half, -HinaPE::Constant::Half, -HinaPE::Constant::Half};
//	auto u = mVector3{HinaPE::Constant::Half, HinaPE::Constant::Half, HinaPE::Constant::Half};
//
//	// bounding box lines
//	_bbox_lines->add(mVector3(l.x(), l.y(), l.z()), mVector3(u.x(), l.y(), l.z()), _opt.color);
//	_bbox_lines->add(mVector3(u.x(), l.y(), l.z()), mVector3(u.x(), u.y(), l.z()), _opt.color);
//	_bbox_lines->add(mVector3(u.x(), u.y(), l.z()), mVector3(l.x(), u.y(), l.z()), _opt.color);
//	_bbox_lines->add(mVector3(l.x(), u.y(), l.z()), mVector3(l.x(), l.y(), l.z()), _opt.color);
//
//	_bbox_lines->add(mVector3(l.x(), l.y(), u.z()), mVector3(u.x(), l.y(), u.z()), _opt.color);
//	_bbox_lines->add(mVector3(u.x(), l.y(), u.z()), mVector3(u.x(), u.y(), u.z()), _opt.color);
//	_bbox_lines->add(mVector3(u.x(), u.y(), u.z()), mVector3(l.x(), u.y(), u.z()), _opt.color);
//	_bbox_lines->add(mVector3(l.x(), u.y(), u.z()), mVector3(l.x(), l.y(), u.z()), _opt.color);
//
//	_bbox_lines->add(mVector3(l.x(), l.y(), l.z()), mVector3(l.x(), l.y(), u.z()), _opt.color);
//	_bbox_lines->add(mVector3(u.x(), l.y(), l.z()), mVector3(u.x(), l.y(), u.z()), _opt.color);
//	_bbox_lines->add(mVector3(u.x(), u.y(), l.z()), mVector3(u.x(), u.y(), u.z()), _opt.color);
//	_bbox_lines->add(mVector3(l.x(), u.y(), l.z()), mVector3(l.x(), u.y(), u.z()), _opt.color);
//
//	_grids = std::make_shared<InstancedLines>(_bbox_lines);
//
//	for (auto &pose: _poses)
//		_grids->_opt.instance_matrices.push_back(pose.get_model_matrix());
//	_grids->_opt.dirty = true;
//}
//void Kasumi::GridObject::update()
//{
//}
//void Kasumi::GridObject::_draw()
//{
//	_grids->render(*_shader);
//}
