//#ifndef KASUMI_POINTS_H
//#define KASUMI_POINTS_H
//
//// Copyright (c) 2023 Xayah Hina
//// MPL-2.0 license
//
//#include "object3D.h"
//namespace Kasumi
//{
//class PointsObject final : public Object3D, public Renderable, public VALID_CHECKER
//{
//public:
//	static void Init();
//	static std::shared_ptr<PointsObject> DefaultPoints;
//
//	void add(const mVector3 &point, const mVector3 &color = HinaPE::Color::PURPLE);
//	void clear();
//
//public:
//	PointsObject();
//
//protected:
//	void _draw() final;
//	void _update_uniform() final;
//
//private:
//	PointsPtr _points;
//};
//using PointsObjectPtr = std::shared_ptr<PointsObject>;
//} // namespace Kasumi
//
//#endif //KASUMI_POINTS_H
