#include "glad/glad.h"
#include "shader_painter.h"

Kasumi::ShaderPainter::ShaderPainter() : Kasumi::App(), _vao(0) { close_benchmark(); }

void Kasumi::ShaderPainter::load_shader(const char *pixel_shader_src)
{
	static std::string painter_vertex_src = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    TexCoords = aTexCoords;
}
)";
	_shader = std::make_shared<Shader>(painter_vertex_src.c_str(), pixel_shader_src);
}

void Kasumi::ShaderPainter::prepare()
{
	_drawing_board = std::make_shared<Kasumi::Framebuffer>(_opt.width, _opt.height);
	// draw a rectangle to fill the screen
	std::array<float, 24> screen_vertices = {
			-1.0, -1.0, 0.0, 0.0,
			-1.0, 1.0, 0.0, 1.0,
			1.0, -1.0, 1.0, 0.0,

			1.0, -1.0, 1.0, 0.0,
			-1.0, 1.0, 0.0, 1.0,
			1.0, 1.0, 1.0, 1.0
	};
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &screen_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(0));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	_drawing_board->render_callback = [&]() // render the scene to the drawing board
	{
		if (_shader == nullptr) return;
#ifdef __APPLE__
		static mVector2 screen(2 * _opt.width, 2 * _opt.height);
#else
		static mVector2 screen(_opt.width, _opt.height);
#endif
		static std::chrono::steady_clock::time_point _starting_point = std::chrono::steady_clock::now();
		float time = static_cast<float>(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - _starting_point).count()) / 1000000.f;
		_shader->use();
		_shader->uniform("iResolution", screen);
		_shader->uniform("iTime", time);
		glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	};
}

void Kasumi::ShaderPainter::update(double dt) { _drawing_board->render(); }
