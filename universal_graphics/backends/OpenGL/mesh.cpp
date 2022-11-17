#include "../../mesh.h"

#include <glad/glad.h>

Kasumi::TexturedMesh::TexturedMesh(std::vector<Vertex> &&vertices, std::vector<Index> &&indices, std::map<std::string, TexturePtr> &&diffuse_textures, std::map<std::string, TexturePtr> &&specular_textures, std::map<std::string, TexturePtr> &&normal_textures,
                                   std::map<std::string, TexturePtr> &&height_textures) : _verts(std::move(vertices)), _idxs(std::move(indices)), _diffuse_textures(std::move(diffuse_textures)), _specular_textures(std::move(specular_textures)),
                                                                                       _normal_textures(std::move(normal_textures)), _height_textures(std::move(height_textures)), _shader(nullptr)
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
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (2 * sizeof(mVector3)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (2 * sizeof(mVector3) + sizeof(mVector2)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) (3 * sizeof(mVector3) + sizeof(mVector2)));
    glEnableVertexAttribArray(4);
    glVertexAttribIPointer(5, 1, GL_UNSIGNED_INT, sizeof(Vertex), (GLvoid *) (4 * sizeof(mVector3) + sizeof(mVector2)));
    glEnableVertexAttribArray(5);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBindVertexArray(0);

    n_elem = _idxs.size();
    _bbox.reset();
    for (auto &v: _verts)
        _bbox.merge(v.position);
    dirty = true;
    is_inited = true;
}
#include <iostream>
Kasumi::TexturedMesh::~TexturedMesh()
{
    glDeleteBuffers(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &EBO);
    VAO = VBO = EBO = 0;

    std::cout << "DELETED!!! "<< std::endl;
}

void Kasumi::TexturedMesh::render()
{
    if (dirty)
        update();

    _shader->bind();

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (GLuint) n_elem, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Kasumi::TexturedMesh::update()
{
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * _verts.size(), &_verts[0], GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * _idxs.size(), &_idxs[0], GL_DYNAMIC_DRAW);

    glBindVertexArray(0);

    dirty = false;
}

void Kasumi::TexturedMesh::use_shader(const Kasumi::ShaderPtr &shader)
{
    _shader = shader;
}
