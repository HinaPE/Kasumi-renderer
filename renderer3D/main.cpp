#include "app.h"
#include "scene.h"

class App : public Kasumi::App
{
protected:
	void prepare() final
	{
		_scene = std::make_shared<Kasumi::Scene3D>();

		{
			auto cube = std::make_shared<Kasumi::CubeObject>();
			cube->sync_opt();
			_scene->add(cube);
		}
		{
			auto sphere = std::make_shared<Kasumi::SphereObject>();
			sphere->sync_opt();
			_scene->add(sphere);
		}

		{
			auto particles = std::make_shared<Kasumi::ParticlesObject>();
			Kasumi::Pose pose1;
			pose1.position = {-5, 0, 0};
			pose1.scale = {5, 5, 5};
			Kasumi::Pose pose2;
			pose2.position = {5, 0, 0};
			pose2.scale = {5, 5, 5};
			particles->_opt.poses.push_back(pose2);
			particles->_opt.poses.push_back(pose1);
			particles->sync_opt();
			_scene->add(particles);
		}

		_scene->VALID_CHECK();
		inspect(_scene);
	}
	void update(double dt) final { _scene->draw(); }

private:
	Kasumi::Scene3DPtr _scene;
};

auto main() -> int
{
	std::make_shared<App>()->launch();
	return 0;
}