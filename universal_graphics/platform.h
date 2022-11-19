#ifndef KASUMI_PLATFORM_H
#define KASUMI_PLATFORM_H

#include "GLFW/glfw3.h"

#include <string>
#include <vector>
#include <map>
#include <functional>
#include <memory>
#include <tuple>
#include <iostream>

namespace Kasumi
{
class App
{
public:
    virtual void prepare() = 0;
    virtual void render() = 0;
    virtual auto quit() -> bool = 0;
    virtual void key(int key, int scancode, int action, int mods) = 0;
    virtual void mouse_button(int button, int action, int mods) = 0;
    virtual void mouse_scroll(double x_offset, double y_offset) = 0;
    virtual void mouse_cursor(double x_pos, double y_pos) = 0;
};
class Platform
{
public:
    void launch(const std::shared_ptr<App> &app);
    void add_key_callback(std::function<void(int key, int scancode, int action, int mods)> &&callback);
    void add_mouse_callback(std::function<void(int button, int action, int mods)> &&callback);
    void add_scroll_callback(std::function<void(double x_offset, double y_offset)> &&callback);
    void add_cursor_callback(std::function<void(double x_pos, double y_pos)> &&callback);

public:
    struct Opt
    {
        bool clear_color = true;
        bool clear_depth = true;
        bool clear_stencil = true;
    };
    Opt opt;

public:
    Platform(int width, int height);
    Platform(const Platform &) = delete;
    Platform(Platform &&) = delete;
    ~Platform() = default;
    auto operator=(const Platform &) -> Platform & = delete;
    auto operator=(Platform &&) -> Platform & = delete;

private:
    void add_new_window(int width, int height, const std::string &title, const std::tuple<float, float, float> &clear_color);
    void rendering_loop(const std::shared_ptr<App> &app);
    void clear_window();
    void begin_frame();
    void end_frame();

private:
    bool _inited;
    std::string _current_window_name;
    GLFWwindow *_current_window;
    std::map<std::string, GLFWwindow *> _windows;
    std::map<std::string, std::tuple<float, float, float>> _clear_colors;
    std::vector<std::function<void(int key, int scancode, int action, int mods)>> _key_callbacks;
    std::vector<std::function<void(int button, int action, int mods)>> _mouse_callbacks;
    std::vector<std::function<void(double xoffset, double yoffset)>> _scroll_callbacks;
    std::vector<std::function<void(double xpos, double ypos)>> _cursor_callbacks;
};
using PlatformPtr = std::shared_ptr<Platform>;
}

#endif //KASUMI_PLATFORM_H
