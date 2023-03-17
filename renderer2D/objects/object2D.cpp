#include "glad/glad.h"
#include "object2D.h"

#ifdef HINAPE_DOUBLE
#define GL_REAL GL_DOUBLE
#else
#define GL_REAL GL_FLOAT
#endif

Kasumi::Object2D::Object2D() : _vao(0), _vbo(0), _ebo(0), _shader(Shader::Default2DShader)
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glVertexAttribPointer(0, 2, GL_REAL, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, position)); // location = 0, position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_REAL, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, color)); // location = 1, color
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBindVertexArray(0);

	_dirty = true;
}

void Kasumi::Object2D::render()
{
	if (_vertices.empty())
		return;

	_shader->use();
	_shader->uniform("pos", POSE.position);
	_shader->uniform("rot", POSE.rotation);
	_shader->uniform("scl", POSE.scale);

	if (_dirty)
		_update();

	glBindVertexArray(_vao);
	if (_type == ObjectType::Triangle)
		glDrawElements(GL_TRIANGLES, (GLsizei) _indices.size(), GL_UNSIGNED_INT, nullptr);
	else if (_type == ObjectType::Line)
		glDrawElements(GL_LINES, (GLsizei) _indices.size(), GL_UNSIGNED_INT, nullptr);
	else if (_type == ObjectType::Point)
		glDrawElements(GL_POINTS, (GLsizei) _indices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}
void Kasumi::Object2D::set_color(const mVector3 &color)
{
	_dirty = true;
	for (auto &v: _vertices)
		v.color = color;
}
void Kasumi::Object2D::_update()
{
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, (GLsizei) (sizeof(Vertex) * _vertices.size()), &_vertices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (sizeof(unsigned int) * _indices.size()), &_indices[0], GL_DYNAMIC_DRAW);
	glBindVertexArray(0);

	_dirty = false;
}
