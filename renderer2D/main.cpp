#include "app.h"
#include "scene.h"

class App2D : public Kasumi::App
{
protected:
	void prepare() final
	{
		_scene = std::make_shared<Kasumi::Scene2D>();

//		{
//			auto lines = std::make_shared<Kasumi::Lines2DObject>();
//			lines->add({-0.9, 0}, {0.9, 0});
//			lines->add({0, -0.9}, {0, 0.9});
//			_scene->add(lines);
//		}

		{
			auto points = std::make_shared<Kasumi::Points2DObject>();
			points->add({0, 0}, HinaPE::Color::MIKU);
			_scene->add(points);
		}

		{
			auto triangle = std::make_shared<Kasumi::Triangle2DObject>();
			triangle->_opt.p1 = {-0.5, -0.5};
			triangle->_opt.p2 = {0.5, -0.5};
			triangle->_opt.p3 = {0, 0.5};
			triangle->_opt.color = HinaPE::Color::RED;
			_scene->add(triangle);
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