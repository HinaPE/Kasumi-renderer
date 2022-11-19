#include "app.h"

Kasumi::Workbench::App::App() : _scene(std::move(std::make_shared<Scene>())), _manager(std::move(std::make_shared<Manager>())), _undo(std::move(std::make_shared<Undo>())) {}

void Kasumi::Workbench::App::prepare()
{
    auto camera_id = _scene->add_camera();
    auto shader_id = _scene->add_shader(std::string(ShaderDir) + "default_shader_vertex.glsl", std::string(ShaderDir) + "default_shader_fragment.glsl");
    auto ayaka = _scene->add_model("F:/Projects/Kasumi-renderer/models/ayaka_uniform/ayaka.pmx", shader_id);
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
