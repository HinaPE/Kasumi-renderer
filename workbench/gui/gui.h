#ifndef KASUMI_GUI_H
#define KASUMI_GUI_H

namespace Kasumi::Workbench
{
class Gui
{
public:
    virtual void render() = 0;
    void key(int key, int scancode, int action, int mods) {};
    void mouse_button(int button, int action, int mods) {};
    void mouse_scroll(double x_offset, double y_offset) {};
    void mouse_cursor(double x_pos, double y_pos) {};
};
}
#endif //KASUMI_GUI_H
