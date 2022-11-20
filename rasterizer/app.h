#ifndef KASUMI_APP_H
#define KASUMI_APP_H

#include "platform.h"

namespace Kasumi::Rasterizer
{
class App : public Kasumi::App
{
public:
    void prepare() final;
    void render() final;
    auto quit() -> bool final;
    void key(int key, int scancode, int action, int mods) final;
    void mouse_button(int button, int action, int mods) final;
    void mouse_scroll(double x_offset, double y_offset) final;
    void mouse_cursor(double x_pos, double y_pos) final;

public:
    explicit App(std::string scene);
};
}

#endif //KASUMI_APP_H
