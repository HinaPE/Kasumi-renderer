#ifndef KASUMI_APP_H
#define KASUMI_APP_H

#include "platform.h"
#include "model.h"
#include "scene/scene.h"
#include "scene/undo.h"
#include "gui/manager.h"

namespace Kasumi::Workbench
{
class App : public Kasumi::App
{
public:
    void render() final;
    void event(GLFWwindow *window) final; // keyboard event and mouse event

public:
    App();
    App(const App &) = delete;
    App(App &&) = delete;
    ~App() = default;
    auto operator=(const App &) -> App & = delete;
    auto operator=(App &&) -> App & = delete;

private:
    ManagerPtr manager;
    ScenePtr scene;
    UndoPtr undo;
};
}

#endif //KASUMI_APP_H
