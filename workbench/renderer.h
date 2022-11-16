#ifndef KASUMI_RENDERER_H
#define KASUMI_RENDERER_H

#include "graphics_api/mesh.h"
#include "graphics_api/shader.h"
#include "graphics_api/framebuffer.h"
#include "graphics_api/graphics_api.h"

namespace Kasumi::Workbench
{
class Renderer final
{
public:
    static void setup(int width, int height);
    static auto get() -> Renderer &;
    static void shutdown();

public:
    Renderer(int width, int height); // DO NOT USE THIS CONSTRUCTOR DIRECTLY
    ~Renderer() = default; // DO NOT USE THIS DESTRUCTOR DIRECTLY

public:
    struct RenderOpt
    {
        unsigned int id;
        mMatrix4x4 model;
        bool surface = true;
        bool wireframe = false;
        bool bbox;
    };
    void mesh(ColoredMesh& mesh, const RenderOpt& opt);
    void mesh(TexturedMesh &mesh, const RenderOpt &opt);

private:
    static inline std::shared_ptr<Renderer> _instance;
    FramebufferPtr _builtin_framebuffer;
    ShaderPtr _builtin_mesh_shader, _builtin_line_shader, _builtin_instance_shader;
    TexturedMeshPtr _builtin_sphere, _builtin_cube;
};
using RendererPtr = std::shared_ptr<Renderer>;
}

#endif //KASUMI_RENDERER_RENDERER_H
