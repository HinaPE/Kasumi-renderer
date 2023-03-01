#ifndef KASUMI_CUBE_H
#define KASUMI_CUBE_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"
namespace Kasumi
{
class CubeObject : public ObjectMesh3D
{
public:
	struct Opt
	{
		real width = 1;
		real height = 1;
		real depth = 1;
	} _opt;
	CubeObject();
	void sync_opt() final;
	void INSPECT() override;
};
using CubeObjectPtr = std::shared_ptr<CubeObject>;
} // namespace Kasumi

#endif //KASUMI_CUBE_H
