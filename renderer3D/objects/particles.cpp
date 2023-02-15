#include "particles.h"
void Kasumi::ParticlesObject::_draw()
{
	if (_mesh == nullptr)
		return;

	_mesh->render(*_shader);
}
void Kasumi::ParticlesObject::sync_opt()
{
	if (!Object3D::_opt.dirty)
		return;

	if (!_opt.texture_path.empty())
		_mesh = std::make_shared<InstancedMesh>(std::make_shared<Mesh>(_opt.mesh_name, _opt.texture_path));
	else
		_mesh = std::make_shared<InstancedMesh>(std::make_shared<Mesh>(_opt.mesh_name, _opt.color));

	for (auto &pose: _opt.poses)
		_mesh->_opt.instance_matrices.push_back(pose.get_model_matrix());
	_mesh->_opt.dirty = true;

	Object3D::sync_opt();
}
