#ifndef KASUMI_PARTICLES_H
#define KASUMI_PARTICLES_H

#include "object3D.h"

namespace Kasumi
{
class ParticlesObject : public Object3D, public Renderable, public VALID_CHECKER
{
public:
	void switch_surface() const { _mesh->_opt.dirty = true; _mesh->_opt.render_surface = !_mesh->_opt.render_surface; }
	void switch_wireframe() const { _mesh->_opt.dirty = true; _mesh->_opt.render_wireframe = !_mesh->_opt.render_wireframe; }
	void switch_bbox() const { _mesh->_opt.dirty = true; _mesh->_opt.render_bbox = !_mesh->_opt.render_bbox; }

public:
	struct Opt
	{
		std::string mesh_name = "sphere";
		std::string texture_path; // Default: not
		mVector3 color = HinaPE::Color::RED;
		std::vector<Pose> poses;
	} _opt;
	ParticlesObject() { _shader = Shader::DefaultInstanceShader; }
	void sync_opt() final;

protected:
	void _draw() final;

protected:
	InstancedMeshPtr _mesh;
};
using ParticlesObjectPtr = std::shared_ptr<ParticlesObject>;
} // namespace Kasumi

#endif //KASUMI_PARTICLES_H
