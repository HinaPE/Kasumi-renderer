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
//    _rotation = mQuaternion::();
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
