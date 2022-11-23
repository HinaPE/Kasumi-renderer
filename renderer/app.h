#ifndef KASUMI_APP_H
#define KASUMI_APP_H

#include "platform.h"
#include "model.h"
#include "shader.h"
#include "camera.h"
#include "scene/scene.h"
#include "scene/undo.h"
#include "gui/manager.h"
#include "api.h"

namespace Kasumi::Workbench
{
class App : public Kasumi::App
{
public:
    void load_api(const Kasumi::ApiPtr& api);

public:
    void prepare() final;
    void update(double dt) final;
    auto quit() -> bool final;
    void key(int key, int scancode, int action, int mods) final;
    void mouse_button(int button, int action, int mods) final;
    void mouse_scroll(double x_offset, double y_offset) final;
    void mouse_cursor(double x_pos, double y_pos) override;

public:
    App(std::string scene);
    App(const App &) = delete;
    App(App &&) = delete;
    ~App() = default;
    auto operator=(const App &) -> App & = delete;
    auto operator=(App &&) -> App & = delete;

private:
    ManagerPtr _manager;
    ScenePtr _scene;
    UndoPtr _undo;
    std::vector<Kasumi::ApiPtr> _apis;
};
}

#endif //KASUMI_APP_H
