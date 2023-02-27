#ifndef HINAPE_RENDERER3D_H
#define HINAPE_RENDERER3D_H

#include "backends/api.h"
#include "scene.h"

namespace Kasumi
{
class Renderer3D : public App
{
public:
	Renderer3D() : _scene(std::make_shared<Kasumi::Scene3D>()) {}
	void add_obj(const Object3DPtr &obj) { _scene->add(obj); }
	virtual void init() {}
	virtual void step(real dt) {}

protected:
	void prepare() final
	{
		init();
//		Kasumi::LinesObject::Init();
//		_scene->add(Kasumi::LinesObject::DefaultLines);
//
		{
			auto cube = std::make_shared<Kasumi::CubeObject>();
			cube->NAME = "cube";
			cube->_rebuild_();
			_scene->add(cube);
		}
//		{
//			auto sphere = std::make_shared<Kasumi::SphereObject>();
//			sphere->NAME = "sphere";
//			sphere->_rebuild_();
//			_scene->add(sphere);
//		}
//		{
//			auto cup = std::make_shared<Kasumi::CupObject>();
//			cup->NAME = "cup";
//			cup->_rebuild_();
//			_scene->add(cup);
//		}
//		{
//			auto grid = std::make_shared<Kasumi::GridObject>();
//			grid->NAME = "grid";
//			grid->init(nullptr);
//			_scene->add(grid);
//		}
//		{
//			auto particles = std::make_shared<Kasumi::ParticlesObject>();
//			particles->NAME = "particles";
//			Kasumi::Pose pose1;
//			pose1.position = {-5, 0, 0};
//			pose1.scale = {5, 5, 5};
//			Kasumi::Pose pose2;
//			pose2.position = {5, 0, 0};
//			pose2.scale = {5, 5, 5};
//			particles->_opt.poses.push_back(pose2);
//			particles->_opt.poses.push_back(pose1);
//			particles->_rebuild_();
//			_scene->add(particles);
//		}

		{
			auto plane = std::make_shared<Kasumi::PlaneObject>();
			plane->NAME = "plane";
			plane->_rebuild_();
			_scene->add(plane);
		}

//		Kasumi::LinesObject::DefaultLines->add({-2, 0, 0}, {2, 0, 0}, HinaPE::Color::RED);

//		inspect(_scene);
//		_scene->VALID_CHECK();
	}
	void update(double dt) final
	{
		HINA_TRACK(step(dt), "Step");
		HINA_TRACK(_scene->draw(), "Rendering");
	}
	void key(int key, int scancode, int action, int mods) override { _scene->key(key, scancode, action, mods); }
	void mouse_button(int button, int action, int mods) override { _scene->mouse_button(button, action, mods); }
	void mouse_scroll(double x_offset, double y_offset) override { _scene->mouse_scroll(x_offset, y_offset); }
	void mouse_cursor(double x_pos, double y_pos) override { _scene->mouse_cursor(x_pos, y_pos); }

protected:
	Kasumi::Scene3DPtr _scene;
};
}

#endif //HINAPE_RENDERER3D_H
