#ifndef KASUMI_MANAGER_H
#define KASUMI_MANAGER_H

#include "scene/scene.h"

#include <vector>
#include <memory>

namespace Kasumi
{
class Gui;
using GuiPtr = std::shared_ptr<Gui>;
class Manager
{
public:
	void load_api(const GuiPtr &gui);
	void render(const ScenePtr &scene, float &start_x, float &start_y);
	auto quit() -> bool;

public:
	Manager(ScenePtr scene);
	Manager(const Manager &) = delete;
	Manager(Manager &&) = delete;
	~Manager() = default;
	auto operator=(const Manager &) -> Manager & = delete;
	auto operator=(Manager &&) -> Manager & = default;

private:
	friend class Renderer;
	void key(int key, int scancode, int action, int mods);
	void mouse_button(int button, int action, int mods);
	void mouse_scroll(double x_offset, double y_offset);
	void mouse_cursor(double x_pos, double y_pos);

private:
	ScenePtr _scene;
	std::vector<std::shared_ptr<Gui>> _gui;
};
using ManagerPtr = std::shared_ptr<Manager>;
class Gui
{
public:
	virtual void render() = 0;

private:
	friend class Manager;
	void key(int key, int scancode, int action, int mods) {};
	void mouse_button(int button, int action, int mods) {};
	void mouse_scroll(double x_offset, double y_offset) {};
	void mouse_cursor(double x_pos, double y_pos) {};

protected:
	ScenePtr _scene;
};
using GuiPtr = std::shared_ptr<Gui>;
}
#endif //KASUMI_MANAGER_H
