#ifndef KASUMI_APP_H
#define KASUMI_APP_H

#include "platform.h"
#include "model.h"
#include "shader.h"
#include "scene/scene.h"
#include "scene/undo.h"
#include "gui/manager.h"

namespace Kasumi::Workbench
{
class App : public Kasumi::App
{
public:
    void prepare() final;
    void render() final;
    void event(GLFWwindow *window) final; // keyboard event and mouse event
    auto get_scene() -> ScenePtr { return _scene; }

public:
    App();
    App(const App &) = delete;
    App(App &&) = delete;
    ~App() = default;
    auto operator=(const App &) -> App & = delete;
    auto operator=(App &&) -> App & = delete;

private:
    ManagerPtr _manager;
    ScenePtr _scene;
    UndoPtr _undo;
};
}

#endif //KASUMI_APP_H
