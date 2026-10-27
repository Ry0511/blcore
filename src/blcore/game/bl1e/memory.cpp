#include "blcore/pch.h"

#ifdef WILLOW64

#include "blcore/game/game.h"

// not mapped for BL1E yet, never reached while GMalloc isn't found
namespace blcore::game {

void* malloc(void* /*gmalloc*/, size_t /*size*/) {
    return nullptr;
}

void* realloc(void* /*gmalloc*/, void* /*original*/, size_t /*size*/) {
    return nullptr;
}

void free(void* /*gmalloc*/, void* /*data*/) {}

}  // namespace blcore::game

#endif  // WILLOW64
