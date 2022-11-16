#ifndef KASUMI_MODEL_H
#define KASUMI_MODEL_H

#include "texture.h"
#include "mesh.h"

#include <map>
#include <string>
#include <memory>

namespace Kasumi
{
class Model
{
public:
    void load(const std::string &path);
    void render();

public:
    Model(const std::string &path);
    Model(const Model &) = delete;
    Model(Model &&) = delete;
    ~Model() = default;
    auto operator=(const Model &) -> Model & = delete;
    auto operator=(Model &&) -> Model & = delete;

private:

private:
    const std::string _path;
    std::map<std::string, TexturedMesh> _meshes;
    std::map<std::string, Texture> _textures;
};
using ModelPtr = std::shared_ptr<Model>;
}

#endif //KASUMI_MODEL_H
