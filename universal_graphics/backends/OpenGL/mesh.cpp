#include "../../mesh.h"

#include <glad/glad.h>

Kasumi::TexturedMesh::TexturedMesh(std::vector<Vertex> &&vertices, std::vector<Index> &&indices) : _verts(std::move(vertices)), _idxs(std::move(indices))
{
    VAO = VBO = EBO = 0;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) sizeof(mVector3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (2 * sizeof(mVector3)));
    glEnableVertexAttribArray(2);

    glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(Vertex), (GLvoid *) (2 * sizeof(mVector3) + sizeof(mVector2)));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBindVertexArray(0);

    n_elem = _idxs.size();
    _bbox.reset();
    for (auto &v: _verts)
        _bbox.merge(v.position);
    dirty = true;
}

Kasumi::TexturedMesh::TexturedMesh(const std::string &path)
{

}

Kasumi::TexturedMesh::~TexturedMesh()
{
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &EBO);
    VAO = VBO = EBO = 0;
}

void Kasumi::TexturedMesh::render()
{
    if (dirty)
        update();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLint)n_elem, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Kasumi::TexturedMesh::update()
{
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _verts.size(), _verts.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * _idxs.size(), _idxs.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);

    dirty = false;
}

void Kasumi::TexturedMesh::attach_texture(const Kasumi::TexturePtr &texture) { _textures.emplace_back(texture); }
