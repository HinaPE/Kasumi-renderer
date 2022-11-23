#ifndef KASUMI_UNDO_H
#define KASUMI_UNDO_H

#include <memory>

namespace Kasumi::Workbench
{
class Undo
{
public:

public:
    Undo() = default;
    Undo(const Undo &) = delete;
    Undo(Undo &&) = delete;
    ~Undo() = default;
    auto operator=(const Undo &) -> Undo & = delete;
    auto operator=(Undo &&) -> Undo & = delete;

public:

};
using UndoPtr = std::shared_ptr<Undo>;
}
#endif //KASUMI_UNDO_H
