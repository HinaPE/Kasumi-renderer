#ifndef KASUMI_OBJECT2D_H
#define KASUMI_OBJECT2D_H

#include "api.h"
#include "pose.h"

namespace Kasumi
{
class Object2D : public INSPECTOR
{
public:
	static unsigned int ID_GLOBAL;
	const unsigned int ID;
	struct Opt
	{
		bool dirty = true;
		Pose2D pose;
	} _opt;
	Object2D() : ID(ID_GLOBAL++) {}
	virtual void sync_opt() { _opt.dirty = false; }

	void INSPECT() override;
};
using Object2DPtr = std::shared_ptr<Object2D>;
} // namespace Kasumi

#endif //KASUMI_OBJECT2D_H
