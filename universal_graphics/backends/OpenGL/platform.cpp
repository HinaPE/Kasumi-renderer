#include "glad/glad.h" // include glad before glfw
#include "../../platform.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "../../model.h"

Kasumi::Platform::Platform(int width, int height) : _inited(false), _current_window(nullptr)
{
    add_new_window(width, height, "Kasumi: illumine the endless night", {1.f, 1.f, 1.f});
    add_key_callback([&]()
                     {
                         if (glfwGetKey(_current_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                             glfwSetWindowShouldClose(_current_window, true);
                     });
}

void Kasumi::Platform::launch(const std::shared_ptr<App> &app) { rendering_loop(app); }
void Kasumi::Platform::add_key_callback(std::function<void()> &&callback) { _key_callbacks.emplace_back(std::move(callback)); }
void Kasumi::Platform::add_mouse_callback(std::function<void()> &&callback) { _mouse_callbacks.emplace_back(std::move(callback)); }

void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }
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
    glfwSetFramebufferSizeCallback(_current_window, framebuffer_size_callback);

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
    Kasumi::Model model("F:/Projects/Kasumi-renderer/models/ayaka_uniform/ayaka.pmx");
    while (!glfwWindowShouldClose(_current_window) || app->quit())
    {
        begin_frame();
        app->event(_current_window);
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
        glClear(GL_DEPTH_BUFFER_BIT);
    if (opt.clear_stencil)
        glClear(GL_STENCIL_BUFFER_BIT);
}

void Kasumi::Platform::process_input()
{
    for (auto &&callback: _key_callbacks)
        callback();
    for (auto &&callback: _mouse_callbacks)
        callback();
}

void Kasumi::Platform::begin_frame()
{
    clear_window();
    process_input();
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