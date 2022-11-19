#include "glad/glad.h" // include glad before glfw
#include "../../platform.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

Kasumi::Platform::Platform(int width, int height) : _inited(false), _current_window(nullptr)
{
    add_new_window(width, height, "Kasumi: illumine the endless night", {1.f, 1.f, 1.f});
    add_key_callback([&](int key, int scancode, int action, int mods) // key call back
                     {
                         if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                             glfwSetWindowShouldClose(_current_window, true);
                     });
}

void Kasumi::Platform::launch(const std::shared_ptr<App> &app)
{
    app->prepare();
    add_key_callback([&](int key, int scancode, int action, int mods)
                     {
                         app->key(key, scancode, action, mods);
                     });
    add_mouse_callback([&](int button, int action, int mods)
                       {
                           app->mouse_button(button, action, mods);
                       });
    add_scroll_callback([&](double x_offset, double y_offset)
                        {
                            app->mouse_scroll(x_offset, y_offset);
                        });
    add_cursor_callback([&](double x_pos, double y_pos)
                        {
                            app->mouse_cursor(x_pos, y_pos);
                        });
    rendering_loop(app);
}
void Kasumi::Platform::add_key_callback(std::function<void(int, int, int, int)> &&callback) { _key_callbacks.emplace_back(std::move(callback)); }
void Kasumi::Platform::add_mouse_callback(std::function<void(int, int, int)> &&callback) { _mouse_callbacks.emplace_back(std::move(callback)); }
void Kasumi::Platform::add_scroll_callback(std::function<void(double, double)> &&callback) { _scroll_callbacks.emplace_back(std::move(callback)); }
void Kasumi::Platform::add_cursor_callback(std::function<void(double, double)> &&callback) { _cursor_callbacks.emplace_back(std::move(callback)); }

void Kasumi::Platform::add_new_window(int width, int height, const std::string &title, const std::tuple<float, float, float> &clear_color)
{
    if (!_inited)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    _current_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    _current_window_name = title;
    _windows[title] = _current_window;
    _clear_colors[title] = clear_color;
    if (_current_window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(_current_window);
    glfwSetWindowUserPointer(_current_window, this);
    glfwSetFramebufferSizeCallback(_current_window, [](GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); });
    glfwSetKeyCallback(_current_window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        auto platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
        for (auto &callback: platform->_key_callbacks)
            callback(key, scancode, action, mods);
    });
    glfwSetMouseButtonCallback(_current_window, [](GLFWwindow *window, int button, int action, int mods)
    {
        auto platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
        for (auto &callback: platform->_mouse_callbacks)
            callback(button, action, mods);
    });
    glfwSetScrollCallback(_current_window, [](GLFWwindow *window, double xoffset, double yoffset)
    {
        auto platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
        for (auto &callback: platform->_scroll_callbacks)
            callback(xoffset, yoffset);
    });
    glfwSetCursorPosCallback(_current_window, [](GLFWwindow *window, double xpos, double ypos)
    {
        auto platform = static_cast<Platform *>(glfwGetWindowUserPointer(window));
        for (auto &callback: platform->_cursor_callbacks)
            callback(xpos, ypos);
    });

    if (!_inited)
    {
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            std::cerr << "Failed to initialize GLAD" << std::endl;
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(_current_window, true); // TODO: install callbacks?
        ImGui_ImplOpenGL3_Init();
        _inited = true;
    }
}

void Kasumi::Platform::rendering_loop(const std::shared_ptr<App> &app)
{
    while (!glfwWindowShouldClose(_current_window) || app->quit())
    {
        begin_frame();
        app->render();
        end_frame();
    }
}

void Kasumi::Platform::clear_window()
{
    if (opt.clear_color)
    {
        auto color = _clear_colors[_current_window_name];
        glClearColor(std::get<0>(color), std::get<1>(color), std::get<2>(color), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    if (opt.clear_depth)
    {
        glEnable(GL_DEPTH_TEST);
        glClear(GL_DEPTH_BUFFER_BIT);
    }
    if (opt.clear_stencil)
        glClear(GL_STENCIL_BUFFER_BIT);
}

void Kasumi::Platform::begin_frame()
{
    clear_window();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Kasumi::Platform::end_frame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(_current_window);
    glfwPollEvents();
}
