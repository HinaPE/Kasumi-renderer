#include "camera.h"
Kasumi::Camera::Camera(Kasumi::mVector2 dim)
{
    reset();
    _aspect_ratio = dim.x / dim.y;
}

void Kasumi::Camera::reset()
{
    _vertical_fov = static_cast<real>(90);
    _aspect_ratio = static_cast<real>(1.7778);
    _rotation = mQuaternion::fromEulerAngles(mVector3(1, 1, 1));
    _near_plane = static_cast<real>(0.01);
    _radius = static_cast<real>(5);
    _radius_sens = static_cast<real>(0.25);
    _move_sens = static_cast<real>(0.015);
    _orbit_sens = static_cast<real>(0.2);
    _aperture = static_cast<real>(0);
    _focal_dist = static_cast<real>(1);
    _look_at = mVector3();
    update();
}

void Kasumi::Camera::update()
{
    _position = _rotation.mul(mVector3(0, 0, 1)).normalized().mul(_radius).add(_look_at);
    iview = mMatrix4x4::makeTranslationMatrix(_position) * _rotation.matrix4();
    view = iview.inverse();
}

auto Kasumi::Camera::front() -> Kasumi::mVector3
{
    return _look_at - _position;
}

auto Kasumi::Camera::distance() -> Kasumi::real
{
    return (_position - _look_at).length();
}

auto Kasumi::Camera::project(float fov, float aspect_ratio, float near) -> Kasumi::mMatrix4x4
{
    Kasumi::mMatrix4x4 res;
    float f = 1.0f / std::tan(fov / 2.0f);
    res(0, 0) = f / aspect_ratio;
    res(1, 1) = f;
    res(2, 2) = 0.0f;
    res(3, 3) = 0.0f;
    res(3, 2) = near;
    res(2, 3) = -1.0f;
    return res;
}

void Kasumi::Camera::loot_at(const Kasumi::mVector3 &center, const Kasumi::mVector3 &pos)
{
    _position = pos;
    _look_at = center;
    _radius = (_position - _look_at).length();
    if (front().dot(mVector3(0, 1, 0)) == -1.0f)
        _rotation = mQuaternion::fromEulerAngles(mVector3(static_cast<real>(270), static_cast<real>(0), static_cast<real>(0)));
//    else
//        _rotation = mQuaternion::fromEulerAngles(mMatrix4x4::makeRotationMatrix(front(), 1)); TODO: fix this
    update();
}
