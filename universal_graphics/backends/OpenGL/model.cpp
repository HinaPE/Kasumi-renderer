#include "../../model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

Kasumi::Model::Model(const std::string &path) : _path(path) { load(path); }

static auto process_mesh(aiMesh *mesh, const aiScene *scene) -> Kasumi::TexturedMesh
{
    Kasumi::TexturedMesh res;
    return res;
}

static void process_node(aiNode *node, const aiScene *scene, std::map<std::string, Kasumi::TexturedMesh> &_meshes)
{
    for (int i = 0; i < node->mNumMeshes; ++i)
    {
        auto *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes[std::string(mesh->mName.data)] = process_mesh(mesh, scene);
    }
    for (unsigned int i = 0; i < node->mNumChildren; i++)
        process_node(node->mChildren[i], scene, _meshes);
}

void Kasumi::Model::load(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        return;

    const std::string directory = path.substr(0, path.find_last_of('/'));

    process_node(scene->mRootNode, scene, _meshes);
}

void Kasumi::Model::render()
{

}
