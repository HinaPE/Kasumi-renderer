#ifndef KASUMI_OBJECT3D_H
#define KASUMI_OBJECT3D_H

#include "backends/api.h"

namespace Kasumi
{
class Object3D : public INSPECTOR
{
public:
	static unsigned int ID_GLOBAL;
	const unsigned int ID;
	std::string NAME = "Untitled";
	struct Opt
	{
		bool dirty = true;
		Pose pose;
	} _opt;
	Object3D() : ID(ID_GLOBAL++) {}
	virtual void _rebuild_() { _opt.dirty = false; }

	void INSPECT() override;
};
using Object3DPtr = std::shared_ptr<Object3D>;

// @formatter:off
class ObjectMesh3D : public Object3D, public Renderable, public VALID_CHECKER
{
public:
	void switch_surface() const { _mesh->_opt.dirty = true;_mesh->_opt.render_surface = !_mesh->_opt.render_surface; }
	void switch_wireframe() const { _mesh->_opt.dirty = true;_mesh->_opt.render_wireframe = !_mesh->_opt.render_wireframe; }
	void switch_bbox() const { _mesh->_opt.dirty = true;_mesh->_opt.render_bbox = !_mesh->_opt.render_bbox; }

public:
	struct Opt
	{
		std::string mesh_name = "cube";
		std::string texture_path; // Default: not
		mVector3 color = HinaPE::Color::RED;
	} _opt;
	ObjectMesh3D() { _shader = Shader::DefaultMeshShader; }
	void _rebuild_() override;

protected:
	void _draw() final;
	void _update_uniform() final;

	void INSPECT() override;
	void VALID_CHECK() const override;

	MeshPtr _mesh;
};
using ObjectMesh3DPtr = std::shared_ptr<ObjectMesh3D>;
// @formatter:on

} // namespace Kasumi
#endif //KASUMI_OBJECT3D_H
