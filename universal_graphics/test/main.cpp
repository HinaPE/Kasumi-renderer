#include "../platform.h"

class MyApp : public Kasumi::App
{
public:
    void event() override
    {

    }
    void render() override
    {

    }
    void quit() override
    {

    }
};

auto main() -> int
{
    auto app = std::make_shared<MyApp>();
    std::make_shared<Kasumi::Platform>(1024, 768)->launch(app);
    return 0;
}
