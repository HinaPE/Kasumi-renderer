#ifndef KASUMI_CAMERA_H
#define KASUMI_CAMERA_H

#include "math_api.h"

namespace Kasumi
{
class Camera final
{
public:
    Camera(mVector2 dim);

public:
    static auto project(float fov, float aspect_ratio, float near) -> mMatrix4x4;

private:
    void reset();
    void update();
    auto front() -> mVector3;
    auto distance() -> real;
    void loot_at(const mVector3& center, const mVector3& pos);

    bool _orbit_flip_vertical = false;

private:
    mVector3 _position, _look_at;
    mQuaternion _rotation;
    real _vertical_fov, _aspect_ratio, _near_plane, _radius, _orbit_sens, _move_sens, _radius_sens, _aperture, _focal_dist;
    mMatrix4x4 view, iview;
};
using CameraPtr = std::shared_ptr<Camera>;
}

#endif //KASUMI_CAMERA_H
