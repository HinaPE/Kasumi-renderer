#include "platform.h"
#include "../app.h"

void test_model()
{
    Kasumi::Model model("/Users/xayah/Downloads/nahida/nahida.pmx");
}

auto main() -> int
{
    test_model();
    auto app = std::make_shared<Kasumi::Workbench::App>();
    std::make_shared<Kasumi::Platform>(1024, 768)->launch(app);
    return 0;
}
