#include "../app.h"

auto main() -> int
{
#ifdef WIN32
    system("chcp 65001");
#endif
    auto platform = std::make_shared<Kasumi::Platform>(1024, 768);
    auto app = std::make_shared<Kasumi::Pathtracer::App>();
    platform->launch(app);
    return 0;
}
