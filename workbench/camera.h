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
    void look_at(mVector3 eye, mVector3 center, mVector3 up);

private:
    mVector3 _position, _look_at;
    real _vertical_fov, _aspect_ratio;
    mQuaternion _rotation;
    mMatrix4x4 view, iview;
};
using CameraPtr = std::shared_ptr<Camera>;
}

#endif //KASUMI_CAMERA_H
