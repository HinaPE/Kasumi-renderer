#ifndef HINAPE_DEFERRED_RENDERER3D_H
#define HINAPE_DEFERRED_RENDERER3D_H

// Copyright (c) 2023 Xayah Hina
// MPL-2.0 license

#include "backends/api.h"
#include "backends/objects/sphere.h"

namespace Kasumi
{
class DeferredRenderer3D : public App
{
public:
	static DeferredRenderer3D DEFAULT_RENDERER; // Default Instance of DeferredRenderer3D

public:
	// temporary methods
	void add_object(const ObjectMesh3DPtr &object);

protected:
	void prepare() final;
	void update(double dt) final;
	auto quit() -> bool final;
	void key(int key, int scancode, int action, int mods) final;
	void mouse_button(int button, int action, int mods) final;
	void mouse_scroll(double x_offset, double y_offset) final;
	void mouse_cursor(double x_pos, double y_pos) final;

private:
	std::map<unsigned int, ObjectMesh3DPtr> _objects;
};
} // namespace Kasumi

#endif //HINAPE_DEFERRED_RENDERER3D_H
