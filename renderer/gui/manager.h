#ifndef KASUMI_MANAGER_H
#define KASUMI_MANAGER_H

#include "scene/scene.h"

#include <memory>
#include <map>

namespace Kasumi
{
class Gui;
class Manager
{
public:
    void render(const ScenePtr& scene, float &start_x, float &start_y);
    auto quit() -> bool;

public:
    Manager();
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
	std::map<std::string, std::shared_ptr<Gui>> _gui;
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
};
}
#endif //KASUMI_MANAGER_H
