#ifndef HINAPE_SHAPE_H
#define HINAPE_SHAPE_H

namespace Kasumi
{
struct Shape
{
	virtual ~Shape() = default;
};
struct Sphere : public Shape
{
	float radius;
};
struct Box : public Shape
{
	mVector2 size;
};
}
#endif //HINAPE_SHAPE_H
