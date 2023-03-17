#ifndef KASUMI_OBJECT2D_H
#define KASUMI_OBJECT2D_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/api.h"

namespace Kasumi
{
class Object2D : public Pose2DBase, public IDBase, public NameBase
{
public:
	virtual void set_color(const mVector3 &color) final;
	virtual void render() final;
	const ShaderPtr _shader;
	Object2D();

	struct Vertex
	{
		mVector2 position;
		mVector3 color = HinaPE::Color::MIKU;;
	};

protected:
	virtual void _update();

	unsigned int _vao, _vbo, _ebo;
	std::vector<Vertex> _vertices;
	std::vector<unsigned int> _indices;
	bool _dirty = true;
};
using Object2DPtr = std::shared_ptr<Object2D>;
} // namespace Kasumi

#endif //KASUMI_OBJECT2D_H
