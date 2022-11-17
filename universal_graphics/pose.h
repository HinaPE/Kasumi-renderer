#ifndef KASUMI_POSE_H
#define KASUMI_POSE_H

#include "math_api.h"

namespace Kasumi
{
class Pose
{
public:
    mVector3 position;
    mVector3 euler;
    mVector3 scale;
};
}
#endif //KASUMI_POSE_H
