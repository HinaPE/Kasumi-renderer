#include "../instance.h"

Kasumi::Instance::Instance(Kasumi::TexturedMeshPtr &&mesh) : _textured_mesh(std::move(mesh)) {}
Kasumi::Instance::Instance(Kasumi::ColoredMeshPtr &&mesh) : _colored_mesh(std::move(mesh)) {}
Kasumi::Instance::~Instance() {}
void Kasumi::Instance::render() {}
