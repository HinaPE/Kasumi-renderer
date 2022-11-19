#ifndef KASUMI_SCENE_OBJECT_H
#define KASUMI_SCENE_OBJECT_H

#include "pose.h"
#include "model.h"
#include <variant>
#include <memory>

namespace Kasumi::Workbench
{
class SceneObject
{
public:
    void render();
    void update_mvp(const mMatrix4x4 &view, const mMatrix4x4 &projection);
    void use_shader(const ShaderPtr &shader);

public:
    template<typename T>
    SceneObject(const T &ptr) : _underlying(ptr) {}
    SceneObject(const SceneObject &) = delete;
    SceneObject(SceneObject &&) = delete;
    ~SceneObject() = default;
    auto operator=(const SceneObject &) -> SceneObject & = delete;
    auto operator=(SceneObject &&) -> SceneObject & = delete;

private:
    Pose pose;
    std::variant<ModelPtr, TexturedMeshPtr> _underlying;
};
using SceneObjectPtr = std::shared_ptr<SceneObject>;
}
#endif //KASUMI_SCENE_OBJECT_H
