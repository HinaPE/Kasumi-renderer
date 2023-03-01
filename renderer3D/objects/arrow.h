#ifndef HINAPE_ARROW_H
#define HINAPE_ARROW_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"

namespace Kasumi
{
class ArrowObject : public ObjectMesh3D
{
public:
	struct Opt
	{
		mVector3 origin = mVector3::Zero();
		mVector3 direction = mVector3::UnitZ();
	} _opt;
	void INSPECT() override;
	ArrowObject();
	void sync_opt() final;
};
using ArrowObjectPtr = std::shared_ptr<ArrowObject>;
} // namespace Kasumi

#endif //HINAPE_ARROW_H
