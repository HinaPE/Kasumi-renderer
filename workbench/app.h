#ifndef KASUMI_APP_H
#define KASUMI_APP_H

#include <SDL.h>

namespace Kasumi::Workbench
{
class App
{
public:
    void render();
    void event(SDL_Event e);
    auto quit() -> bool;
};
}

#endif //KASUMI_APP_H
