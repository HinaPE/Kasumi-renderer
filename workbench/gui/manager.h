#ifndef KASUMI_MANAGER_H
#define KASUMI_MANAGER_H

#include "scene/scene.h"
#include "scene/undo.h"
#include <memory>

namespace Kasumi::Workbench
{
class Manager
{
public:
    void render_3d(ScenePtr &scene, UndoPtr &undo);
    void render_gui(ScenePtr &scene, UndoPtr &undo);

public:
    Manager() = default;
    Manager(const Manager &) = delete;
    Manager(Manager &&) = delete;
    ~Manager() = default;
    auto operator=(const Manager &) -> Manager & = delete;
    auto operator=(Manager &&) -> Manager & = delete;

public:

};
using ManagerPtr = std::shared_ptr<Manager>;
}
#endif //KASUMI_MANAGER_H
