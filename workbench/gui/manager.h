#ifndef KASUMI_MANAGER_H
#define KASUMI_MANAGER_H

#include <memory>

namespace Kasumi::Workbench
{
class Manager
{
public:
    Manager() = default;
    Manager(const Manager &) = delete;
    Manager(Manager &&) = delete;
    ~Manager() = default;
    auto operator=(const Manager &) -> Manager & = delete;
    auto operator=(Manager &&) -> Manager & = delete;
};
using ManagerPtr = std::shared_ptr<Manager>;
}
#endif //KASUMI_MANAGER_H
