#ifndef KASUMI_SIMULATE_H
#define KASUMI_SIMULATE_H

#include "manager.h"
#include "framebuffer.h"

namespace Kasumi
{
class Simulate : public Gui
{
public:
	explicit Simulate(int width = 1500, int height = 700);

public:
    void render() final;

private:
	FramebufferPtr _debug_frame;
};
}
#endif //KASUMI_SIMULATE_H
