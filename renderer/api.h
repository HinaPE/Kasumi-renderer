#ifndef KASUMI_API_H
#define KASUMI_API_H

#include <memory>

namespace Kasumi
{
class Scene;
using ScenePtr = std::shared_ptr<Scene>;
class Api
{
public:
    virtual void step(ScenePtr &scene, float dt) = 0;
    virtual void ui_menu(ScenePtr &scene) {};
    virtual void ui_sidebar(ScenePtr &scene) {};
};
using ApiPtr = std::shared_ptr<Api>;
}

#endif //KASUMI_API_H
