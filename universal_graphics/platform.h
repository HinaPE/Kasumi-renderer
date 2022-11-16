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
    virtual void render() = 0;
    virtual void event(GLFWwindow *) {};
    virtual void quit() {};
};
class Platform
{
public:
    void launch(const std::shared_ptr<App> &app);
    void add_key_callback(std::function<void()> &&callback);
    void add_mouse_callback(std::function<void()> &&callback);

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
    void process_input();

private:
    bool _inited;
    std::string _current_window_name;
    GLFWwindow *_current_window;
    std::map<std::string, GLFWwindow *> _windows;
    std::map<std::string, std::tuple<float, float, float>> _clear_colors;
    std::vector<std::function<void()>> _key_callbacks;
    std::vector<std::function<void()>> _mouse_callbacks;
};
using PlatformPtr = std::shared_ptr<Platform>;
}

#endif //KASUMI_PLATFORM_H
