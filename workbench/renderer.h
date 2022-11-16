#ifndef KASUMI_RENDERER_WORKBENCH_H
#define KASUMI_RENDERER_WORKBENCH_H

#include "graphics_api/mesh.h"
#include "graphics_api/shader.h"
#include "graphics_api/framebuffer.h"
#include "graphics_api/graphics_api.h"

namespace Kasumi::Workbench
{
class Renderer final
{
public:
    struct RenderOpt
    {
        unsigned int id;
        mMatrix4x4 model;
        bool surface = true;
        bool wireframe = false;
        bool bbox;
    };
    void render();
    void mesh(ColoredMesh &mesh, const RenderOpt &opt);
    void mesh(TexturedMesh &mesh, const RenderOpt &opt);

public:
    Renderer(int width, int height);
    Renderer(const Renderer &) = delete;
    Renderer(Renderer &&) = delete;
    ~Renderer() = default;
    auto operator=(const Renderer &) -> Renderer & = delete;
    auto operator=(Renderer &&) -> Renderer & = delete;

private:
    FramebufferPtr _builtin_framebuffer;
    ShaderPtr _builtin_mesh_shader, _builtin_line_shader, _builtin_instance_shader;
    TexturedMeshPtr _builtin_sphere, _builtin_cube;
};
using RendererPtr = std::shared_ptr<Renderer>;
}

#endif //KASUMI_RENDERER_WORKBENCH_H
