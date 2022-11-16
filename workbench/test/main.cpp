#include "platform.h"
#include "../app.h"

auto main() -> int
{
    auto app = std::make_shared<Kasumi::Workbench::App>();
    std::make_shared<Kasumi::Platform>(1024, 768)->launch(app);
    return 0;
}
