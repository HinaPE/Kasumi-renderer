#include "platform.h"
#include "../app.h"

auto main() -> int
{
#ifdef WIN32
    system("chcp 65001");
#endif
    auto app = std::make_shared<Kasumi::Workbench::App>();
    std::make_shared<Kasumi::Platform>(1024, 768)->launch(app);
    return 0;
}
