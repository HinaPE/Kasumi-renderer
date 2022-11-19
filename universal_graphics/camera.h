#ifndef KASUMI_CAMERA_H
#define KASUMI_CAMERA_H

#include "math_api.h"

namespace Kasumi
{
class Camera final
{
public:
    void loot_at(const mVector3 &focus_point);
    auto get_projection() const -> mMatrix4x4;
    auto get_view() const -> mMatrix4x4;

public:
    struct Opt
    {
        // for view
        mVector3 position; // auto calculated: _opt.position = _opt.look_at + _opt.rotation * mVector3(0, 0, _opt.radius);
        mQuaternion rotation = mQuaternion{1, 0, 0, 0};
        mVector3 look_at = mVector3(0, 0, 0);
        real radius = 20;

        // for projection
        real vertical_fov = 45;
        real aspect_ratio = 1024.f / 768.f;
        real near_plane = 0.01;
        real far_plane = 100;

        // mouse control
        real orbit_sens = 0.2;
        real move_sens = 0.015;
        real radius_sens = 0.25;

        // lens parameters
        real aperture = 0; // not used yet
        real focal_dist = 1; // not used yet
        bool orbit_flip_vertical = false;
    } _opt;

public:
    Camera(Opt opt);
    Camera(const Camera &) = delete;
    Camera(Camera &&) = default;
    ~Camera() = default;
    auto operator=(const Camera &) -> Camera & = delete;
    auto operator=(Camera &&) -> Camera & = default;

private:
    static auto project_matrix(real fov, real aspect_ratio, real near, real far) -> mMatrix4x4;
    static auto view_matrix(const mVector3 &position, const mQuaternion &rotation) -> mMatrix4x4;
    void update();
    auto up() const -> mVector3;
    auto front() const -> mVector3;
    auto distance() const -> real;

private:
    mMatrix4x4 _projection, _view;
};
using CameraPtr = std::shared_ptr<Camera>;
}

#endif //KASUMI_CAMERA_H
