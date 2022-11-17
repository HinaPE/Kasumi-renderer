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
    auto load(const std::string &path) -> bool;
    void render();

public:
    Model() = default;
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
};
using ModelPtr = std::shared_ptr<Model>;
}

#endif //KASUMI_MODEL_H
