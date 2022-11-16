#include "../workbench/platform.h"

auto main(int argc, char **argv) -> int
{
    Kasumi::Workbench::Platform plt(800, 600);
    Kasumi::Workbench::App app;
    plt.update(app);
    return 0;
}
