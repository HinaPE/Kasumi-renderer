#ifndef KASUMI_SCENE_OBJECT_H
#define KASUMI_SCENE_OBJECT_H

#include <memory>

namespace Kasumi::Workbench
{
class SceneObject
{
public:
    SceneObject() = default;
    SceneObject(const SceneObject &) = delete;
    SceneObject(SceneObject &&) = delete;
    ~SceneObject() = default;
    auto operator=(const SceneObject &) -> SceneObject & = delete;
    auto operator=(SceneObject &&) -> SceneObject & = delete;
};
using SceneObjectPtr = std::shared_ptr<SceneObject>;
}
#endif //KASUMI_SCENE_OBJECT_H
