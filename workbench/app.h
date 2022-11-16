#ifndef KASUMI_APP_H
#define KASUMI_APP_H

#include "platform.h"

namespace Kasumi::Workbench
{
class App : public Kasumi::App
{
public:
    void render() final {}
    void event(GLFWwindow *window) override
    {
        Kasumi::App::event(window);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            std::cout << "Hello Kasumi" << std::endl;
    }
};
}

#endif //KASUMI_APP_H
