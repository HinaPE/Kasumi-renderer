#ifndef KASUMI_INSTANCE_H
#define KASUMI_INSTANCE_H

#include "mesh.h"

namespace Kasumi
{
class Instance
{
public:
    Instance(TexturedMeshPtr &&mesh);
    Instance(ColoredMeshPtr &&mesh);
    Instance(const Instance &) = delete;
    Instance(Instance &&) = default;
    ~Instance();
    auto operator=(const Instance &) -> Instance & = delete;
    auto operator=(Instance &&) -> Instance & = default;

public:
    void render();

private:
    TexturedMeshPtr _textured_mesh;
    ColoredMeshPtr _colored_mesh;
};
}

#endif //KASUMI_INSTANCE_H
