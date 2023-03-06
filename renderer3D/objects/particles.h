//#ifndef KASUMI_PARTICLES_H
//#define KASUMI_PARTICLES_H
//
//// Copyright (c) 2023 Xayah Hina
//// MPL-2.0 license
//
//#include "object3D.h"
//
//namespace Kasumi
//{
//class ParticlesObject : public Object3D, public Renderable, public VALID_CHECKER
//{
//public:
//	void _switch_surface() const { _mesh->_opt.dirty = true; _mesh->_opt.render_surface = !_mesh->_opt.render_surface; }
//	void _switch_wireframe() const { _mesh->_opt.dirty = true; _mesh->_opt.render_wireframe = !_mesh->_opt.render_wireframe; }
//	void _switch_bbox() const { _mesh->_opt.dirty = true; _mesh->_opt.render_bbox = !_mesh->_opt.render_bbox; }
//
//public:
//	struct Opt
//	{
//		std::string mesh_name = "cube";
//		std::string texture_path; // Default: not
//		mVector3 color = HinaPE::Color::ORANGE;
//		std::vector<Pose> poses;
//	} _opt;
//	ParticlesObject();
//	void init();
//	void INSPECT() override;
//	void _rebuild_();
//
//protected:
//	void _draw() final;
//
//protected:
//	InstancedMeshPtr _mesh;
//};
//using ParticlesObjectPtr = std::shared_ptr<ParticlesObject>;
//} // namespace Kasumi
//
//#endif //KASUMI_PARTICLES_H
