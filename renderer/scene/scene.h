#ifndef KASUMI_SCENE_H
#define KASUMI_SCENE_H

#include "camera.h"
#include "scene_object.h"

#include <map>
#include <memory>
#include <functional>
#include <limits>

namespace Kasumi
{
class Scene
{
public:
	auto read_scene(const std::string &path) -> std::string /** return: error message */;
	auto write_to_file(const std::string &path) -> std::string /** return: error message */;

public:
	void render();

public: //! ==================== Scene Objects properties ====================
	inline auto get_camera() -> CameraPtr & { return _scene_camera; }
	inline auto get_object(unsigned int id) -> SceneObjectPtr { return _scene_objects.count(id) == 1 ? _scene_objects[id] : nullptr; }
	auto add_object(ModelPtr &o) -> unsigned int;
	auto add_object(ModelPtr &&o) -> unsigned int;
	void erase_object(unsigned int id);
	void restore_object(unsigned int id);
private:
	std::map<unsigned int, SceneObjectPtr> _scene_objects;
	std::map<unsigned int, SceneObjectPtr> _scene_objects_erased;
	CameraPtr _scene_camera;

public: //! ==================== Scene Objects properties ====================
	struct State
	{
		unsigned int selected_object_id = std::numeric_limits<unsigned int>::max();
		unsigned int selected_camera_id = std::numeric_limits<unsigned int>::max();
	} _state;

//! Constructors & Destructor
//! - [DELETE] copy constructor & copy assignment operator
//! - [DELETE] move constructor & move assignment operator
public:
	friend class Renderer;
	Scene();
	Scene(const Scene &) = delete;
	Scene(Scene &&) = delete;
	~Scene();
	auto operator=(const Scene &) -> Scene & = delete;
	auto operator=(Scene &&) -> Scene & = delete;

	void for_each_item(const std::function<void(SceneObjectPtr &)> &func);

private: //! ==================== UI & callbacks ====================
	void key(int key, int scancode, int action, int mods);
	void mouse_button(int button, int action, int mods);
	void mouse_scroll(double x_offset, double y_offset);
	void mouse_cursor(double x_pos, double y_pos);
	void ui_sidebar();

private:
	void clear();
};
using ScenePtr = std::shared_ptr<Scene>;
}
#endif //KASUMI_SCENE_H
