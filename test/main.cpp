#include "../graphics_api/platform_glfw.h"

auto main() -> int
{
    Kasumi::GLFW::Platform platform(1024, 768);
    platform.launch();
    return 0;
}
