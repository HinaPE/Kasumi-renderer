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
public:
	struct Opt
	{
		bool api_running = false;
	} _opt;

public:
	std::shared_ptr<App> load_api(const Kasumi::ApiPtr &api);
	void prepare() final;
	/**
	 * Update Rendering Loop
	 * @param dt
	 */
	void update(double dt) final;
	auto quit() -> bool final;

private:
	friend class Kasumi::Platform;
	void key(int key, int scancode, int action, int mods) final;
	void mouse_button(int button, int action, int mods) final;
	void mouse_scroll(double x_offset, double y_offset) final;
	void mouse_cursor(double x_pos, double y_pos) final;

private:
	void ui_menu();
	void ui_sidebar();
	void reset_state();
	float _next_x = 0.f, _next_y = 0.f;

private:
	ManagerPtr _manager;
	ScenePtr _scene;
	UndoPtr _undo;
	std::vector<Kasumi::ApiPtr> _apis;
	FramebufferPtr _framebuffer; // NOT COMPLETED YET
	std::string _scene_file;

public:
	Renderer(std::string scene_file = "empty.txt");
	Renderer(const Renderer &) = delete;
	Renderer(Renderer &&) = delete;
	~Renderer() = default;
	auto operator=(const Renderer &) -> Renderer & = delete;
	auto operator=(Renderer &&) -> Renderer & = delete;
};
}

#endif //KASUMI_APP_H
