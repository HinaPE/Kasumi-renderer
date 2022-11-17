#include "simulate.h"
#include <iostream>
void Kasumi::Workbench::Simulate::render()
{

}

void Kasumi::Workbench::Simulate::event(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        std::cout << "A" << std::endl;
}
