#ifndef HINAPE_RENDERER3D_H
#define HINAPE_RENDERER3D_H

#include "scene.h"

namespace Kasumi
{
class Renderer3D : public App
{
public:
	void add_obj(const ObjectMesh3DPtr &obj) { _scene->add(obj); }
	void remove_obj(unsigned int id) { _scene->remove(id); }
	Renderer3D() : _scene(std::make_shared<Kasumi::Scene3D>()) {}
	std::function<void(const Kasumi::Scene3DPtr &)> _init;
	std::function<void(real)> _step;

protected:
	void prepare() final
	{
		if (_init) _init(_scene);

		ObjectLines3D::Init();
		_scene->_line_enable = true;
		ObjectPoints3D::Init();
		_scene->_point_enable = true;

		inspect(_scene.get());
		_scene->VALID_CHECK();
	}
	void update(double dt) final
	{
		if (_step) HINA_TRACK(_step(dt), "Step");
		HINA_TRACK(_scene->draw(), "Rendering");
	}
	void key(int key, int scancode, int action, int mods) override { _scene->key(key, scancode, action, mods); }
	void mouse_button(int button, int action, int mods) override { _scene->mouse_button(button, action, mods); }
	void mouse_scroll(double x_offset, double y_offset) override { _scene->mouse_scroll(x_offset, y_offset); }
	void mouse_cursor(double x_pos, double y_pos) override { _scene->mouse_cursor(x_pos, y_pos); }

protected:
	Kasumi::Scene3DPtr _scene;
};
} // namespace Kasumi
// @formatter:on
#endif //HINAPE_RENDERER3D_H
