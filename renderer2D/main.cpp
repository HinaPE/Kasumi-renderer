#include "app.h"
#include "scene.h"

class App2D : public Kasumi::App
{
protected:
	void prepare() final
	{
	}
	void update(double dt) final
	{
	}

private:
};

auto main() -> int
{
	std::make_shared<App2D>()->launch();
	return 0;
}