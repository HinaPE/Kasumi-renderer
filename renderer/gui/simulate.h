#ifndef KASUMI_SIMULATE_H
#define KASUMI_SIMULATE_H

#include "gui.h"

namespace Kasumi
{
class Simulate : public Gui
{
public:
    void render() final;
};
}
#endif //KASUMI_SIMULATE_H