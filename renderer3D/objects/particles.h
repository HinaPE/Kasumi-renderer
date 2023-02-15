#ifndef HINAPE_PARTICLES_H
#define HINAPE_PARTICLES_H

#include "object3D.h"

namespace Kasumi
{
class ParticlesObject final : public Object3D, public Renderable, public VALID_CHECKER
{
public:
	struct Opt
	{
		std::string mesh_name = "cube";
		std::string texture_path; // Default: not
		mVector3 color = HinaPE::Color::RED;
		std::vector<Pose> poses;
	} _opt;
	ParticlesObject() { _shader = Shader::DefaultInstanceShader; }
	void sync_opt() final;

protected:
	void _draw() final;

private:
	InstancedMeshPtr _mesh;
};
using ParticlesObjectPtr = std::shared_ptr<ParticlesObject>;
} // namespace Kasumi
#endif //HINAPE_PARTICLES_H
