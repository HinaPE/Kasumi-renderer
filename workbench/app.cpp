#include "app.h"

Kasumi::Workbench::App::App() : _scene(std::move(std::make_shared<Scene>())), _manager(std::move(std::make_shared<Manager>())), _undo(std::move(std::make_shared<Undo>())) {}

void Kasumi::Workbench::App::prepare()
{
    auto shader = std::make_shared<Shader>(std::string(ShaderDir) + "default_shader_vertex.glsl", std::string(ShaderDir) + "default_shader_fragment.glsl");
    auto ayaka = std::make_shared<Model>("/Users/xayah/Downloads/nahida/nahida.pmx");
    ayaka->use_shader(shader);
    auto obj = std::make_shared<SceneObject>(ayaka);
    _scene->add(std::move(obj));
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
