#ifndef KASUMI_SCENE_OBJECT_H
#define KASUMI_SCENE_OBJECT_H

#include "pose.h"
#include "model.h"
#include "framebuffer.h"

#include <variant>
#include <memory>

namespace Kasumi
{
class SceneObject
{
public:
	auto get_model() -> ModelPtr & { return std::get<ModelPtr>(_underlying); }
	inline auto position() -> mVector3 & { return _pose.position; }
	inline auto rotation() -> mVector3 & { return _pose.euler; }
	inline auto scale() -> mVector3 & { return _pose.scale; }

private:
	std::variant<ModelPtr> _underlying;

public:
	void render();
	void use_custom_shader(const ShaderPtr &shader);
	void update_mvp(const mMatrix4x4 &view, const mMatrix4x4 &projection);
	void update_light(const LightPtr &light);
	void debug_frame_mode(bool mode);
	Pose _pose;
	std::string _name;

public:
	explicit SceneObject(ModelPtr &ptr);
	explicit SceneObject(ModelPtr &&ptr);
	SceneObject(const SceneObject &) = delete;
	SceneObject(SceneObject &&) = delete;
	~SceneObject() = default;
	auto operator=(const SceneObject &) -> SceneObject & = delete;
	auto operator=(SceneObject &&) -> SceneObject & = delete;
};
using SceneObjectPtr = std::shared_ptr<SceneObject>;
}
#endif //KASUMI_SCENE_OBJECT_H
