#ifndef HINAPE_SHADER_PAINTER_H
#define HINAPE_SHADER_PAINTER_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/api.h"

namespace Kasumi
{
class ShaderPainter : public App
{
public:
	ShaderPainter();
	void load_shader(const char* pixel_shader_src);
	Kasumi::ShaderPtr _shader;

protected:
	void prepare() final;
	void update(double dt) final;
	void key(int key, int scancode, int action, int mods) final;

private:
	Kasumi::FramebufferPtr _drawing_board;
	unsigned int _vao;
};
} // namespace Kasumi

#endif //HINAPE_SHADER_PAINTER_H
