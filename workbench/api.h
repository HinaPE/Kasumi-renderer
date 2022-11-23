#ifndef KASUMI_API_H
#define KASUMI_API_H

#include <memory>

namespace Kasumi
{
namespace Workbench
{
class Scene;
using ScenePtr = std::shared_ptr<Scene>;
}
class Api
{
public:
    virtual void step(Workbench::ScenePtr &scene, float dt) = 0;
    virtual void gui(Workbench::ScenePtr &scene) = 0;
};
using ApiPtr = std::shared_ptr<Api>;
}

#endif //KASUMI_API_H
