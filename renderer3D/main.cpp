#include "backends/app.h"
#include "scene.h"

class App : public Kasumi::App
{
protected:
	void prepare() final
	{
		Kasumi::LinesObject::Init();

		_scene = std::make_shared<Kasumi::Scene3D>();
		_scene->add(Kasumi::LinesObject::DefaultLines);

//		{
//			auto cube = std::make_shared<Kasumi::CubeObject>();
//			cube->NAME = "cube";
//			cube->_rebuild_();
//			_scene->add(cube);
//		}
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
		{
			auto grid = std::make_shared<Kasumi::GridObject>();
			grid->NAME = "grid";
			grid->init(nullptr);
			_scene->add(grid);
		}
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

		Kasumi::LinesObject::DefaultLines->add({-2, 0, 0}, {2, 0, 0}, HinaPE::Color::RED);

		inspect(_scene);
		_scene->VALID_CHECK();
	}
	void update(double dt) final { _scene->draw(); }
	void key(int key, int scancode, int action, int mods) final { _scene->key(key, scancode, action, mods); }
	void mouse_button(int button, int action, int mods) final { _scene->mouse_button(button, action, mods); }
	void mouse_scroll(double x_offset, double y_offset) final { _scene->mouse_scroll(x_offset, y_offset); }
	void mouse_cursor(double x_pos, double y_pos) final { _scene->mouse_cursor(x_pos, y_pos); }

private:
	Kasumi::Scene3DPtr _scene;
};

auto main() -> int
{
	std::make_shared<App>()->launch();
	return 0;
}