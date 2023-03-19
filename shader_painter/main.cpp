#include "shader_painter.h"

auto main() -> int
{
	Kasumi::ShaderPainter painter;
	painter.load_shader(std::string(PainterShaderDir) + "cloud.glsl");
	painter.launch();
	return 0;
}