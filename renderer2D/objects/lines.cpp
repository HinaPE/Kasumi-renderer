#include "glad/glad.h"
#include "lines.h"

#ifdef HINAPE_DOUBLE
#define GL_REAL GL_DOUBLE
#else
#define GL_REAL GL_FLOAT
#endif

Kasumi::Lines2DObject::Lines2DObject() : _vao(0), _vbo(0), _ebo(0)
{
	_shader = Shader::Default2DShader;

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(0, 2, GL_REAL, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, position)); // location = 0, position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_REAL, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, color)); // location = 1, color
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
std::shared_ptr<Kasumi::Lines2DObject> Kasumi::Lines2DObject::Default2DLines = nullptr;
void Kasumi::Lines2DObject::Init()
{
	Default2DLines = std::make_shared<Lines2DObject>();
}
void Kasumi::Lines2DObject::add(const mVector2 &start, const mVector2 &end, const mVector3 &color)
{
	Vertex v1, v2;
	v1.position = start;
	v1.color = color;
	v2.position = end;
	v2.color = color;
	_lines.push_back(v1);
	_lines.push_back(v2);
	_dirty = true;
}
void Kasumi::Lines2DObject::_draw()
{
	_shader->use();

	if (_dirty)
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, (GLsizei) (sizeof(Vertex) * _lines.size()), &_lines[0], GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
		_dirty = false;
	}

	glLineWidth(1);
	glEnable(GL_LINE_SMOOTH);
	glBindVertexArray(_vao);
	glDrawArrays(GL_LINES, 0, (GLsizei) _lines.size());
	glBindVertexArray(0);
}
