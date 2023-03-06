//#include "particles.h"
//
//Kasumi::ParticlesObject::ParticlesObject()
//{
//	NAME = "Cup";
//	_shader = Shader::DefaultInstanceShader;
//	if (!_opt.texture_path.empty())
//		_mesh = std::make_shared<InstancedMesh>(std::make_shared<Mesh>(_opt.mesh_name, _opt.texture_path));
//	else
//		_mesh = std::make_shared<InstancedMesh>(std::make_shared<Mesh>(_opt.mesh_name, _opt.color));
//}
//void Kasumi::ParticlesObject::_draw()
//{
//	if (_mesh == nullptr)
//		return;
//
//	_mesh->render(*_shader);
//}
//void Kasumi::ParticlesObject::_rebuild_()
//{
//	if (!_dirty)
//		return;
//
//	_mesh->_opt.instance_matrices.clear();
//	_mesh->_opt.instance_matrices.reserve(_opt.poses.size());
//
//	for (auto &pose: _opt.poses)
//		_mesh->_opt.instance_matrices.push_back(pose.get_model_matrix());
//	_mesh->_opt.dirty = true;
//}
//void Kasumi::ParticlesObject::INSPECT()
//{
//	Object3D::INSPECT();
//
//	ImGui::Text("Particles: %zd", _opt.poses.size());
//}
