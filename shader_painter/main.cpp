#include "shader_painter.h"

#include "imgui.h"

class CloudInspector : public Kasumi::INSPECTOR
{
public:
	explicit CloudInspector(Kasumi::ShaderPtr shader) : _shader(std::move(shader)) {}

protected:
	void INSPECT() final
	{
		static float sigma_a = 0.198;
		ImGui::SliderFloat("sigma_a", &sigma_a, 0.0f, 1.0f);
		_shader->uniform("sigma_a", sigma_a);

		static float sphere_radius = 8.286;
		ImGui::SliderFloat("sphere_radius", &sphere_radius, 0.1f, 10.0f);
		_shader->uniform("sphere_radius", sphere_radius);
	}

	Kasumi::ShaderPtr _shader;
};

auto main() -> int
{
	Kasumi::ShaderPainter painter;
	painter.load_shader(std::string(PainterShaderDir) + "cloud.glsl");
	CloudInspector inspector(painter._shader);
	painter.inspect(&inspector);
	painter.launch();
	return 0;
}