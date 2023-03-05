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
		Kasumi::PointsObject::Init();
		_scene->add(Kasumi::PointsObject::DefaultPoints);
		Kasumi::LinesObject::Init();
		_scene->add(Kasumi::LinesObject::DefaultLines);

		_scene->add(std::make_shared<Kasumi::SphereObject>());

//		Kasumi::PointsObject::DefaultPoints->add({0, 0, 0}, HinaPE::Color::RED);
//		Kasumi::LinesObject::DefaultLines->add({-2, 0, 0}, {2, 0, 0}, HinaPE::Color::RED);

		inspect(_scene.get());
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
