#include "../../model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <map>

Kasumi::Model::Model(const std::string &path) : _path(path), _shader(nullptr) { load(path); }

#include <iostream>
Kasumi::Model::~Model()
{
    std::cout << "delete model: " << _path << std::endl;
}

static auto process_mesh(aiMesh *mesh, const aiScene *scene, const std::string &directory) -> Kasumi::TexturedMeshPtr
{
    std::vector<Kasumi::TexturedMesh::Vertex> vertices;
    std::vector<Kasumi::TexturedMesh::Index> indices;
    std::vector<std::vector<Kasumi::Texture>> textures;

    // Load vertices
    for (int i = 0; i < mesh->mNumVertices; ++i)
    {
        Kasumi::TexturedMesh::Vertex v;
        v.position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        if (mesh->HasNormals())
            v.normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
        if (mesh->HasTextureCoords(0))
            v.tex_coord = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
        if (mesh->HasTangentsAndBitangents())
        {
            v.tangent = {mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};
            v.bi_tangent = {mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
        }
        v.id = i; // TODO: auto id
        vertices.emplace_back(std::move(v));
    }

    // Load indices
    for (int i = 0; i < mesh->mNumFaces; ++i)
        for (int j = 0; j < mesh->mFaces[i].mNumIndices; ++j)
            indices.emplace_back(mesh->mFaces[i].mIndices[j]);

    // Load materials
    auto *materials = scene->mMaterials[mesh->mMaterialIndex];
    auto load_material = [&](aiTextureType type) -> std::map<std::string, Kasumi::TexturePtr>
    {
        std::map<std::string, Kasumi::TexturePtr> res;
        for (int i = 0; i < materials->GetTextureCount(type); ++i)
        {
            aiString path, name;
            materials->GetTexture(type, i, &path);
            std::string cpp_path, cpp_name;
            cpp_path = directory + "/" + std::string(path.C_Str());
            res.emplace(std::move(cpp_name), std::move(std::make_shared<Kasumi::Texture>(cpp_path)));
        }
        return res;
    };

    return std::make_shared<Kasumi::TexturedMesh>(std::move(vertices), std::move(indices), std::move(load_material(aiTextureType_DIFFUSE)), std::move(load_material(aiTextureType_SPECULAR)), std::move(load_material(aiTextureType_HEIGHT)),
                                                  std::move(load_material(aiTextureType_AMBIENT)));
}

static void process_node(aiNode *node, const aiScene *scene, std::map<std::string, Kasumi::TexturedMeshPtr> &_meshes, const std::string &directory)
{
    for (int i = 0; i < node->mNumMeshes; ++i)
    {
        auto *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.emplace(std::string(mesh->mName.C_Str()), std::move(process_mesh(mesh, scene, directory)));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        process_node(node->mChildren[i], scene, _meshes, directory);
}

auto Kasumi::Model::load(const std::string &path) -> bool
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        return false;

    const std::string directory = path.substr(0, path.find_last_of('/'));
    _path = path;

    process_node(scene->mRootNode, scene, _meshes, directory);
    return true;
}

void Kasumi::Model::render()
{
    if (!_shader)
        return;

    _shader->use();
    for (auto &mesh: _meshes)
        mesh.second->render();
}

void Kasumi::Model::use_shader(const Kasumi::ShaderPtr &shader)
{
    _shader = shader;
    for (auto &mesh: _meshes)
        mesh.second->use_shader(shader);
}

auto Kasumi::Model::get_shader() -> Kasumi::ShaderPtr &
{
    return _shader;
}
