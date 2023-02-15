#include "app.h"
#include "scene.h"

class App2D : public Kasumi::App
{
protected:
	void prepare() final
	{
		_scene = std::make_shared<Kasumi::Scene2D>();

		{
			auto triangle = std::make_shared<Kasumi::Triangle2D>();
//			triangle->sync_opt();
			_scene->add(triangle);
		}


		inspect(_scene);
		_scene->VALID_CHECK();
	}
	void update(double dt) final
	{
	}

private:
	Kasumi::Scene2DPtr _scene;
};

auto main() -> int
{
	std::make_shared<App2D>()->launch();
	return 0;
}