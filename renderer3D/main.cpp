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

		_scene->VALID_CHECK();
		inspect(_scene);
	}
	void update(double dt) final
	{
		_scene->draw();
	}

private:
	Kasumi::Scene3DPtr _scene;
};

auto main() -> int
{
	std::make_shared<App>()->launch();
	return 0;
}