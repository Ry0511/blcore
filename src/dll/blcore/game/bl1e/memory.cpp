#include "blcore/pch.h"

#ifdef WILLOW64

#include "blcore/game/game.h"

namespace blcore::game {

void* malloc(void* /*gmalloc*/, size_t /*size*/, uint32_t /*alignment*/) {
    return nullptr;
}

void* realloc(void* /*gmalloc*/, void* /*original*/, size_t /*size*/, uint32_t /*alignment*/) {
    return nullptr;
}

void free(void* /*gmalloc*/, void* /*data*/) {}

}  // namespace blcore::game

#endif  // WILLOW64
