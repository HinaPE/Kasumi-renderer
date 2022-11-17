#include "app.h"

Kasumi::Workbench::App::App() : scene(std::move(std::make_shared<Scene>())), manager(std::move(std::make_shared<Manager>())), undo(std::move(std::make_shared<Undo>())) {}

void Kasumi::Workbench::App::render()
{
    scene->render();
    manager->render();
}

void Kasumi::Workbench::App::event(GLFWwindow *window)
{
    Kasumi::App::event(window);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        std::cout << "Hello Kasumi" << std::endl;
    manager->event(window);
}
