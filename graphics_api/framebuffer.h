#ifndef KASUMI_FRAMEBUFFER_H
#define KASUMI_FRAMEBUFFER_H

#include <memory>

namespace Kasumi
{
class Framebuffer
{
public:
    Framebuffer(int width, int height);

private:
    int _width, _height;
};
using FramebufferPtr = std::shared_ptr<Framebuffer>;
}

#endif //KASUMI_RENDERER_FRAMEBUFFER_H
