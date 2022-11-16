#ifndef KASUMI_APP_H
#define KASUMI_APP_H

namespace Kasumi::Workbench
{
class App
{
public:
    void render();
    void event();
    auto quit() -> bool;
};
}

#endif //KASUMI_APP_H
