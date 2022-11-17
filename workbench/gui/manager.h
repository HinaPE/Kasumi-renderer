#ifndef KASUMI_MANAGER_H
#define KASUMI_MANAGER_H


#include "scene/scene.h"
#include "scene/undo.h"
#include "simulate.h"
#include <memory>

#include <map>

namespace Kasumi::Workbench
{
class Manager
{
public:
    void render();
    void event(GLFWwindow *window);

public:
    Manager();
    Manager(const Manager &) = delete;
    Manager(Manager &&) = delete;
    ~Manager() = default;
    auto operator=(const Manager &) -> Manager & = delete;
    auto operator=(Manager &&) -> Manager & = delete;

private:
    std::map<std::string, std::shared_ptr<Gui>> _gui;
};
using ManagerPtr = std::shared_ptr<Manager>;
}
#endif //KASUMI_MANAGER_H
