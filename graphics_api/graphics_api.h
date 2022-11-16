#ifndef KASUMI_GRAPHICS_API_H
#define KASUMI_GRAPHICS_API_H

#include <glad/glad.h>

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

#endif //KASUMI_GRAPHICS_API_H
