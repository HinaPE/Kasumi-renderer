#ifndef KASUMI_RENDERER_GRAPHICS_API_H
#define KASUMI_RENDERER_GRAPHICS_API_H

namespace Kasumi
{
class GraphicsAPI
{
public:
    static void setup();
    static void shutdown();

public:
    static void wireframe_mode(bool enable);
    static void offset(bool enable);
    static void culling(bool enable);
    static void depth_write(bool enable);
};
}

#endif //KASUMI_RENDERER_GRAPHICS_API_H
