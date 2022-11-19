#include "../../camera.h"
#include "GLFW/glfw3.h"
#include <utility>

static bool left_button_pressed = false;
static bool middle_button_pressed = false;
static bool right_button_pressed = false;
static bool is_left_button_first_click = true;
static bool is_middle_button_first_click = true;
static bool is_right_button_first_click = true;
static double last_mouse_pos_x = 0;
static double last_mouse_pos_y = 0;

Kasumi::Camera::Camera(Kasumi::Camera::Opt opt) : _opt(std::move(opt)) { update(); }

auto Kasumi::Camera::get_projection() const -> Kasumi::mMatrix4x4 { return _projection; }
auto Kasumi::Camera::get_view() const -> Kasumi::mMatrix4x4 { return _view; }

void Kasumi::Camera::key(int key, int scancode, int action, int mods) {}
void Kasumi::Camera::mouse_button(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        left_button_pressed = true;
        is_left_button_first_click = true;
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        left_button_pressed = false;
        is_left_button_first_click = true;
    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
    {
        middle_button_pressed = true;
        is_middle_button_first_click = true;
    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_RELEASE)
    {
        middle_button_pressed = false;
        is_middle_button_first_click = true;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        right_button_pressed = true;
        is_right_button_first_click = true;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        right_button_pressed = false;
        is_right_button_first_click = true;
    }
}
void Kasumi::Camera::mouse_scroll(double x_offset, double y_offset)
{
    _opt.radius -= static_cast<real>(y_offset) * _opt.radius_sens;
    _opt.radius = std::max(_opt.radius, 2.0f * _opt.near_plane);
    update();
}
void Kasumi::Camera::mouse_cursor(double x_pos, double y_pos)
{
    if (left_button_pressed)
    {
        //        if (!is_left_button_first_click)
        //        {
        //        real delta_x = static_cast<real>(x_pos - last_mouse_pos_x);
        //        real delta_y = static_cast<real>(y_pos - last_mouse_pos_y);
        //            mQuaternion q = mQuaternion(mVector3(0, 1, 0), static_cast<real>(delta_x) * _opt.orbit_sens);
        //            q = q * mQuaternion(up(), static_cast<real>(delta_y) * _opt.orbit_sens);
        //            _opt.rotation = q * _opt.rotation;
        //            update();
        //        } else
        //            is_left_button_first_click = false;
        //        last_mouse_pos_x = x_pos;
        //        last_mouse_pos_y = y_pos;
    } else if (middle_button_pressed)
    {
        if (!is_middle_button_first_click)
        {
            real delta_x = static_cast<real>(x_pos - last_mouse_pos_x);
            real delta_y = static_cast<real>(y_pos - last_mouse_pos_y);
            float up_rot = -delta_x * _opt.orbit_sens;
            float right_rot = -delta_y * _opt.orbit_sens;
            if (_opt.orbit_flip_vertical)
                right_rot = -right_rot;
            auto t_up = _opt.rotation * up();
            auto t_front = front();
            auto t_right = t_front.cross(t_up).normalized();
            _opt.rotation = mQuaternion(t_up, up_rot) * mQuaternion(t_right, right_rot) * _opt.rotation;
            update();
        } else
            is_middle_button_first_click = false;
        last_mouse_pos_x = x_pos;
        last_mouse_pos_y = y_pos;
    } else if (right_button_pressed)
    {
        if (!is_right_button_first_click)
        {
            real delta_x = static_cast<real>(x_pos - last_mouse_pos_x);
            real delta_y = static_cast<real>(y_pos - last_mouse_pos_y);
            auto t_up = _opt.rotation * up();
            auto t_front = front();
            auto t_right = t_front.cross(t_up).normalized();
            _opt.look_at += -delta_x * t_right * _opt.move_sens + t_up * delta_y * _opt.move_sens;
            update();
        } else
            is_right_button_first_click = false;
        last_mouse_pos_x = x_pos;
        last_mouse_pos_y = y_pos;
    }
}

void Kasumi::Camera::update()
{
    _opt.position = _opt.look_at + _opt.rotation * mVector3(0, 0, _opt.radius);
    _projection = Camera::project_matrix(_opt.vertical_fov, _opt.aspect_ratio, _opt.near_plane, _opt.far_plane);
    _view = Camera::view_matrix(_opt.position, _opt.rotation);
}

auto Kasumi::Camera::up() const -> Kasumi::mVector3 { return {0, 1, 0}; }
auto Kasumi::Camera::front() const -> Kasumi::mVector3 { return (_opt.look_at - _opt.position).normalized(); }
auto Kasumi::Camera::distance() const -> Kasumi::real { return (_opt.look_at - _opt.position).length(); }
void Kasumi::Camera::loot_at(const mVector3 &focus_point) { _opt.look_at = focus_point; } //TODO: not completed

auto Kasumi::Camera::project_matrix(real fov, real aspect_ratio, real near, real far) -> Kasumi::mMatrix4x4
{
    // get projection matrix
    Kasumi::mMatrix4x4 projection;
    float tan_half_fov = std::tan(fov / static_cast<real>(2));
    projection(0, 0) = static_cast<real>(1) / (aspect_ratio * tan_half_fov);
    projection(1, 1) = static_cast<real>(1) / (tan_half_fov);
    projection(2, 2) = -(far + near) / (far - near);
    projection(3, 2) = -static_cast<real>(1);
    projection(2, 3) = -(static_cast<real>(2) * far * near) / (far - near);
    return projection;
}

auto Kasumi::Camera::view_matrix(const Kasumi::mVector3 &position, const Kasumi::mQuaternion &rotation) -> Kasumi::mMatrix4x4 { return (mMatrix4x4::makeTranslationMatrix(position) * rotation.matrix4()).inverse(); }

