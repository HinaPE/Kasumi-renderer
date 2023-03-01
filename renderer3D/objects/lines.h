#ifndef KASUMI_LINES_H
#define KASUMI_LINES_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "object3D.h"
namespace Kasumi
{
class LinesObject final : public Object3D, public Renderable, public VALID_CHECKER
{
public:
	static void Init();
	static std::shared_ptr<LinesObject> DefaultLines;

	void add(const mVector3 &start, const mVector3 &end, const mVector3 &color = HinaPE::Color::PURPLE);

public:
	LinesObject();

protected:
	void _draw() final;
	void _update_uniform() final;

private:
	LinesPtr _lines;
};
using LinesObjectPtr = std::shared_ptr<LinesObject>;
} // namespace Kasumi

#endif //KASUMI_LINES_H
