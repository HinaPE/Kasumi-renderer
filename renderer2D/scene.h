#ifndef KASUMI_SCENE2_H
#define KASUMI_SCENE2_H

#include "objects/object2D.h"
#include "objects/triangle.h"
#include "objects/lines.h"
#include "objects/points.h"

namespace Kasumi
{
class Scene2D : public VALID_CHECKER, public INSPECTOR
{
public:
	void add(const Object2DPtr& object);
	void remove(unsigned int id);
	void draw();

	void VALID_CHECK() const final;
	void INSPECT() final;

private:
	std::map<unsigned int, Object2DPtr> _objects; // mesh, light
	int selected = 0;
};
using Scene2DPtr = std::shared_ptr<Scene2D>;
} // namespace Kasumi

#endif //KASUMI_SCENE2_H
