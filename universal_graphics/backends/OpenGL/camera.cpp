#include <utility>

#include "../../camera.h"

Kasumi::Camera::Camera(Kasumi::Camera::Opt opt) : _opt(std::move(opt)) { update(); }

void Kasumi::Camera::loot_at(const mVector3 &focus_point)
{
    _opt.look_at = focus_point;
}
auto Kasumi::Camera::get_projection() const -> Kasumi::mMatrix4x4 { return _projection; }
auto Kasumi::Camera::get_view() const -> Kasumi::mMatrix4x4 { return _view; }

void Kasumi::Camera::update()
{
    _opt.position = _opt.look_at + _opt.rotation * mVector3(0, 0, _opt.radius);
//        _projection = Camera::project_matrix(_opt.vertical_fov, _opt.aspect_ratio, _opt.near_plane, _opt.far_plane);
//        _view = Camera::view_matrix(_opt.position, _opt.rotation);
    _projection = mMatrix4x4::makeIdentity();
    _view = mMatrix4x4::makeIdentity();
}

auto Kasumi::Camera::up() const -> Kasumi::mVector3 { return {0, 1, 0}; }
auto Kasumi::Camera::front() const -> Kasumi::mVector3 { return (_opt.look_at - _opt.position).normalized(); }
auto Kasumi::Camera::distance() const -> Kasumi::real { return (_opt.look_at - _opt.position).length(); }

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