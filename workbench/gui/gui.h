#ifndef KASUMI_GUI_H
#define KASUMI_GUI_H

#include "GLFW/glfw3.h"

namespace Kasumi::Workbench
{
class Gui
{
public:
    virtual void render() = 0;
    virtual void event(GLFWwindow *window) = 0;
};
}
#endif //KASUMI_GUI_H
