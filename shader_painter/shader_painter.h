#ifndef HINAPE_SHADER_PAINTER_H
#define HINAPE_SHADER_PAINTER_H

#include "backends/api.h"

namespace Kasumi
{
class ShaderPainter final : public App
{
public:
	ShaderPainter();
	void load_shader(const std::string &pixel_shader);

protected:
	void prepare() final;
	void update(double dt) final;

private:
	Kasumi::FramebufferPtr _drawing_board;
	std::vector<Kasumi::ShaderPtr> _shaders;
	unsigned int _vao{0};
};
} // namespace Kasumi

#endif //HINAPE_SHADER_PAINTER_H
