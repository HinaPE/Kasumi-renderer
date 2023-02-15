#include "app.h"
#include "scene.h"

class App2D : public Kasumi::App
{
protected:
	void prepare() final
	{
		_scene = std::make_shared<Kasumi::Scene2D>();

		{
			auto lines = std::make_shared<Kasumi::Lines2DObject>();
			lines->add({-0.9, 0}, {0.9, 0});
			lines->add({0, -0.9}, {0, 0.9});
			_scene->add(lines);
		}


		inspect(_scene);
		_scene->VALID_CHECK();
	}
	void update(double dt) final
	{
		_scene->draw();
	}

private:
	Kasumi::Scene2DPtr _scene;
};

auto main() -> int
{
	std::make_shared<App2D>()->launch();
	return 0;
}