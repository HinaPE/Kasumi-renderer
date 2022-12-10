#ifndef KASUMI_API_H
#define KASUMI_API_H

#include <memory>

namespace Kasumi
{
class Scene;
using ScenePtr = std::shared_ptr<Scene>;
/**
 * @brief The Api class is the main interface to the renderer.
 */
class Api
{
public:
	/**
	 * @brief Step simulation by timestep
	 * @param dt: physics timestep
	 */
    virtual void step(float dt) = 0;
	/**
	 * setup menu ui
	 */
    virtual void ui_menu() {};
	/**
	 * @brief setup sidebar ui
	 * @example
	 * int a = 0; \n
	 * int b = 1; \n
	 * ui_sidebar(); \n
	 */
    virtual void ui_sidebar() {};

	/**
	 * scene pointer
	 */
    ScenePtr _scene;
};
using ApiPtr = std::shared_ptr<Api>;
}

#endif //KASUMI_API_H
