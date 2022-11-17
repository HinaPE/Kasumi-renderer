#ifndef KASUMI_MESH_H
#define KASUMI_MESH_H

#include "math_api.h"
#include "texture.h"

#include <map>

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
        mVector3 tangent;
        mVector3 bi_tangent;
        unsigned int id;
    };

public:
    TexturedMesh() = default;
    TexturedMesh(std::vector<Vertex> &&vertices, std::vector<Index> &&indices, std::map<std::string, Texture> &&diffuse_textures, std::map<std::string, Texture> &&specular_textures, std::map<std::string, Texture> &&normal_textures,
                 std::map<std::string, Texture> &&height_textures);
    TexturedMesh(const TexturedMesh &src) = delete;
    TexturedMesh(TexturedMesh &&src) noexcept = default;
    ~TexturedMesh();
    void operator=(const TexturedMesh &src) = delete;
    auto operator=(TexturedMesh &&src) noexcept -> TexturedMesh & = default;

public:
    void render();
    void update();

private:
    bool is_inited;
    bool dirty;
    unsigned int VAO, VBO, EBO;
    size_t n_elem;

    std::vector<Vertex> _verts;
    std::vector<Index> _idxs;
    std::map<std::string, Texture> _diffuse_textures;
    std::map<std::string, Texture> _specular_textures;
    std::map<std::string, Texture> _normal_textures;
    std::map<std::string, Texture> _height_textures;
    mBBox _bbox;
};
using TexturedMeshPtr = std::shared_ptr<TexturedMesh>;
}

#endif //KASUMI_MESH_H
