#ifndef KASUMI_SIMULATE_H
#define KASUMI_SIMULATE_H

#include "gui.h"

namespace Kasumi::Workbench
{
class Simulate : public Gui
{
public:
    void render() final;
    void event(GLFWwindow *window) final;
};
}
#endif //KASUMI_SIMULATE_H
