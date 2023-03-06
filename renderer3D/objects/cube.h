#ifndef KASUMI_CUBE_H
#define KASUMI_CUBE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"
namespace Kasumi
{
class CubeObject : public ObjectMesh3D, public HinaPE::Geom::Box3
{
public:
	CubeObject();
	void sync_opt() final {}
};
using CubeObjectPtr = std::shared_ptr<CubeObject>;
} // namespace Kasumi

#endif //KASUMI_CUBE_H
