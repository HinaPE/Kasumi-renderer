#ifndef KASUMI_MESH_H
#define KASUMI_MESH_H

#include "math_api.h"
#include "texture.h"

namespace Kasumi
{
class ColoredMesh final {}; // TODO:
using ColoredMeshPtr = std::shared_ptr<ColoredMesh>;

class TexturedMesh final
{
public:
    using Index = unsigned int;
    struct Vertex
    {
        mVector3 position;
        mVector3 normal;
        mVector2 tex_coord;
        unsigned int id;
    };

public:
    TexturedMesh() = default;
    TexturedMesh(std::vector<Vertex> &&vertices, std::vector<Index> &&indices);
    TexturedMesh(const std::string &path);
    TexturedMesh(const TexturedMesh &src) = delete;
    TexturedMesh(TexturedMesh &&src) noexcept = default;
    ~TexturedMesh();
    void operator=(const TexturedMesh &src) = delete;
    auto operator=(TexturedMesh &&src) noexcept -> TexturedMesh & = default;

public:
    void render();
    void update();
    void attach_texture(const TexturePtr &texture);

private:
    bool dirty;
    unsigned int VAO, VBO, EBO;
    size_t n_elem;

    std::vector<Vertex> _verts;
    std::vector<Index> _idxs;
    std::vector<TexturePtr> _textures;
    mBBox _bbox;
};
using TexturedMeshPtr = std::shared_ptr<TexturedMesh>;
}

#endif //KASUMI_MESH_H
