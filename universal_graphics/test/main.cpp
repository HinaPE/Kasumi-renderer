#include "../platform.h"

class MyApp : public Kasumi::App
{
public:
    void render() final {}
    void event(GLFWwindow *window) override
    {
        App::event(window);
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            std::cout << "Hello Kasumi" << std::endl;
    }
};

auto main() -> int
{
    auto app = std::make_shared<MyApp>();
    std::make_shared<Kasumi::Platform>(1024, 768)->launch(app);
    return 0;
}
