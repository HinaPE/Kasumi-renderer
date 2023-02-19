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
	LinesObject() { _shader = Shader::DefaultLineShader; }
	void _rebuild_() final
	{
		if (!Object3D::_opt.dirty)
			return;

		_lines = std::make_shared<Lines>();

		Object3D::_rebuild_();
	}

protected:
	void _draw() final;
	void _update_uniform() override;

private:
	LinesPtr _lines;
};
using LinesObjectPtr = std::shared_ptr<LinesObject>;
} // namespace Kasumi

#endif //KASUMI_LINES_H
