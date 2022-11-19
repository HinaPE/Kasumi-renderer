#ifndef KASUMI_POSE_H
#define KASUMI_POSE_H

#include "math_api.h"

namespace Kasumi
{
class Pose
{
public:
    auto get_model_matrix() -> mMatrix4x4 &&;

private:
    mVector3 position = {0.0f, -.5f, 0.0f};
    mVector3 euler = {0.0f, 0.0f, 0.0f};
    mVector3 scale = {0.5f, 0.5f, -0.5f};
};
}
#endif //KASUMI_POSE_H
