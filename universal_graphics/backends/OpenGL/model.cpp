#include "../../model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <map>

Kasumi::Model::Model(const std::string &path) : _path(path), _shader(nullptr) { load(path); }

static auto process_mesh(aiMesh *mesh, const aiScene *scene) -> Kasumi::TexturedMesh
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
    auto load_material = [&](aiTextureType type) -> std::map<std::string, Kasumi::Texture>
    {
        std::map<std::string, Kasumi::Texture> res;
        for (int i = 0; i < materials->GetTextureCount(type); ++i)
        {
            aiString path, name;
            materials->GetTexture(type, i, &path);
            std::string cpp_path, cpp_name;
            cpp_path = std::string(path.C_Str());
            Kasumi::Texture temp(cpp_path);
            res.emplace(std::move(cpp_name), std::move(temp));
        }
        return res;
    };

    return {std::move(vertices), std::move(indices), std::move(load_material(aiTextureType_DIFFUSE)), std::move(load_material(aiTextureType_SPECULAR)), std::move(load_material(aiTextureType_HEIGHT)), std::move(load_material(aiTextureType_AMBIENT))};
}

static void process_node(aiNode *node, const aiScene *scene, std::map<std::string, Kasumi::TexturedMesh> &_meshes)
{
    for (int i = 0; i < node->mNumMeshes; ++i)
    {
        auto *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.emplace(std::string(mesh->mName.C_Str()), std::move(process_mesh(mesh, scene)));
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        process_node(node->mChildren[i], scene, _meshes);
}

auto Kasumi::Model::load(const std::string &path) -> bool
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        return false;

    const std::string directory = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene, _meshes);
    return true;
}

void Kasumi::Model::use_shader(const Kasumi::ShaderPtr &shader)
{
    _shader = shader;
}

void Kasumi::Model::render()
{
    if (!_shader)
        return;

    _shader->bind();
    for (auto &mesh: _meshes)
        mesh.second.render();
}
