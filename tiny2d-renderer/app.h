#ifndef HINAPE_APP_H
#define HINAPE_APP_H

// backends includes
#include "platform.h"
#include "model.h"

// kasumi includes
#include "shape.h"
#include "math_api.h"
#include <vector>
namespace Kasumi
{
class Renderer2D : public Kasumi::App
{
public:
	void prepare() final;
	void update(double dt) final;
	auto quit() -> bool final;

public:
	std::vector<Kasumi::Shape> _shapes;
};
}

#endif //HINAPE_APP_H
