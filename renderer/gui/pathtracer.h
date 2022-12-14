#ifndef HINAPE_PATHTRACER_H
#define HINAPE_PATHTRACER_H

#include "manager.h"
#include "framebuffer.h"
namespace Kasumi
{
class Pathtracer : public Gui
{
public:
	explicit Pathtracer(int width = 1500, int height = 700);

public:
	void render() final;

private:
	FramebufferPtr _debug_frame;
};
using PathtracerPtr = std::shared_ptr<Pathtracer>;
}
#endif //HINAPE_PATHTRACER_H
