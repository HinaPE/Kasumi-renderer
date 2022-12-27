#ifndef HINAPE_PATHTRACER_H
#define HINAPE_PATHTRACER_H

//!
//! Mention: NOT COMPLETE YET!
//!

#include "manager.h"
#include "framebuffer.h"
namespace Kasumi
{
class Pathtracer : public Gui
{
public:
	explicit Pathtracer(int width = 1500, int height = 700);

public:
	void render() final;

private:
	FramebufferPtr _pathtracer_frame;

private:


private:
	int sampleSceneIndex = -1;
	int envMapIndex = 0;
	int selectedInstance = 0;
	double lastTime = 0;
	std::string shaderDir;
	std::string assetsDir;
	std::string hdrResDir;

	std::vector<std::string> sceneFiles;
	std::vector<std::string> sceneNames;
	std::vector<std::string> envFiles;
	std::vector<std::string> envNames;
};
using PathtracerPtr = std::shared_ptr<Pathtracer>;
}
#endif //HINAPE_PATHTRACER_H
