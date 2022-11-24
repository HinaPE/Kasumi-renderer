#ifndef KASUMI_SCENE_OBJECT_H
#define KASUMI_SCENE_OBJECT_H

#include "pose.h"
#include "model.h"
#include <variant>
#include <memory>

namespace Kasumi
{
class SceneObject
{
public:
    void render();
    void use_shader(const ShaderPtr &shader);
    void update_mvp(const mMatrix4x4 &view, const mMatrix4x4 &projection);
    Pose _pose;
    unsigned int _id;

public:
    void set_wireframe(bool enable);

private:
    std::variant<ModelPtr, TexturedMeshPtr, ColoredMeshPtr> _underlying;

public:
    template<typename T>
    SceneObject(const T &ptr);
    SceneObject(const SceneObject &) = delete;
    SceneObject(SceneObject &&) = delete;
    ~SceneObject() = default;
    auto operator=(const SceneObject &) -> SceneObject & = delete;
    auto operator=(SceneObject &&) -> SceneObject & = delete;
};
using SceneObjectPtr = std::shared_ptr<SceneObject>;

template<typename T>
Kasumi::SceneObject::SceneObject(const T &ptr) : _underlying(ptr)
{
    std::visit([&](auto &renderable)
               {
                   _pose.position = -renderable->get_center_point();
               }, _underlying);
}
}
#endif //KASUMI_SCENE_OBJECT_H
