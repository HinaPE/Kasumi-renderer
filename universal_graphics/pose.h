#ifndef KASUMI_POSE_H
#define KASUMI_POSE_H

#include "math_api.h"

namespace Kasumi
{
class Pose
{
public:
    auto get_model_matrix() const -> mMatrix4x4 &&;

public:
    mVector3 position = {0, 0, 0};
    mVector3 euler = {0, 0, 0};
    mVector3 scale = {1, 1, 1};
};
}
#endif //KASUMI_POSE_H
