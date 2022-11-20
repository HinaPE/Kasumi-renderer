#include "app.h"

auto main() -> int
{
    std::make_shared<Kasumi::Platform>(1024, 768)->launch(std::make_shared<Kasumi::Pathtracer::App>("miku.txt"));
    return 0;
}
