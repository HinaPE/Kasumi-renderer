#include "glad/glad.h"
#include "points.h"

#ifdef KASUMI_DOUBLE
#define GL_REAL GL_DOUBLE
#else
#define GL_REAL GL_FLOAT
#endif

Kasumi::Points2DObject::Points2DObject() : _vao(0), _vbo(0), _ebo(0)
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
void Kasumi::Points2DObject::add(const mVector2 &pt, const mVector3 &color)
{
	Vertex v;
	v.position = pt;
	v.color = color;
	_points.push_back(v);
	_dirty = true;
}
void Kasumi::Points2DObject::_draw()
{
	_shader->use();

	glPointSize(25);

	if (_dirty)
	{
		glBindVertexArray(_vao);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, (GLsizei) (sizeof(Vertex) * _points.size()), &_points[0], GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
		_dirty = false;
	}

	glLineWidth(1);
	glEnable(GL_LINE_SMOOTH);
	glBindVertexArray(_vao);
	glDrawArrays(GL_POINTS, 0, (GLsizei) _points.size());
	glBindVertexArray(0);
}
