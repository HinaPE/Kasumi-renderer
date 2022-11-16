#include "../../model.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

Kasumi::Model::Model(const std::string &path) : _path(path) { load(path); }

void Kasumi::Model::load(const std::string &path)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    if (!scene)
        return;
}

void Kasumi::Model::render()
{

}
