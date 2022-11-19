#include "app.h"
#include "nfd/nfd.h"

Kasumi::Workbench::App::App() : _scene(std::move(std::make_shared<Scene>())), _manager(std::move(std::make_shared<Manager>())), _undo(std::move(std::make_shared<Undo>())) {}

void Kasumi::Workbench::App::prepare()
{
//    char *scene_file = nullptr;
//    auto res = NFD_OpenDialog("txt", TestDir, &scene_file);
//    if (res == NFD_OKAY)
//    {
//        _scene->read_scene(std::string(scene_file));
//        std::cout << "Success" << std::endl;
//    } else if (res == NFD_CANCEL)
//    {
//        std::cout << "Cancel" << std::endl;
//    } else
//    {
//        std::cout << "Error" << std::endl;
//    }
    _scene->read_scene(std::string(TestDir) + "scene.txt");
}

void Kasumi::Workbench::App::render()
{
    _scene->render();
    _manager->render();
}

void Kasumi::Workbench::App::event(GLFWwindow *window)
{
    Kasumi::App::event(window);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        std::cout << "Hello Kasumi" << std::endl;
    _manager->event(window);
}
