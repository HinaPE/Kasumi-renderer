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
			inspect(cube);
		}

		_scene->VALID_CHECK();
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