#ifndef KASUMI_APP_H
#define KASUMI_APP_H

// backends includes
#include "platform.h"
#include "model.h"
#include "shader.h"
#include "camera.h"
#include "framebuffer.h"

// kasumi includes
#include "scene/scene.h"
#include "scene/undo.h"
#include "gui/manager.h"
#include "api.h"
namespace Kasumi
{
class Renderer : public Kasumi::App
{
public: //! ==================== Public Methods ====================
	auto load_api(const Kasumi::ApiPtr &api) -> std::shared_ptr<App>;
	void prepare() final;
	void update(double dt) final;
	auto quit() -> bool final;

public:
	struct Opt
	{
		bool api_running = false;
	} _opt;

//! ==================== Constructors & Destructor ====================
//! - [DELETE] copy constructor & copy assignment operator
//! - [DELETE] move constructor & move assignment operator
public:
	explicit Renderer(std::string scene_file = "empty.txt", int width = 1920, int height = 768, const std::string& title = "Kasumi Renderer");
	Renderer(const Renderer &) = delete;
	Renderer(Renderer &&) = delete;
	~Renderer() = default;
	auto operator=(const Renderer &) -> Renderer & = delete;
	auto operator=(Renderer &&) -> Renderer & = delete;

private:
	void ui_menu();
	void ui_sidebar();
	void reset_state();
	float _next_x = 0.f, _next_y = 0.f;

private:
	friend class Kasumi::Platform;
	void key(int key, int scancode, int action, int mods) final;
	void mouse_button(int button, int action, int mods) final;
	void mouse_scroll(double x_offset, double y_offset) final;
	void mouse_cursor(double x_pos, double y_pos) final;

private:
	ManagerPtr _manager;
	ScenePtr _scene;
	UndoPtr _undo;
	std::vector<Kasumi::ApiPtr> _apis;
	std::string _scene_file;
};
}

#endif //KASUMI_APP_H
