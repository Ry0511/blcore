#include "blcore/pch.h"

#include "blcore/game/bl1e/game_impl.h"

namespace blcore::game::bl1e {

// TODO: implement this

void* GameImpl::malloc(void* /*gmalloc*/, size_t /*size*/, uint32_t /*alignment*/) const {
    return nullptr;
}

void* GameImpl::realloc(
    void* /*gmalloc*/,
    void* /*original*/,
    size_t /*size*/,
    uint32_t /*alignment*/
) const {
    return nullptr;
}

void GameImpl::free(void* /*gmalloc*/, void* /*data*/) const {}

}  // namespace blcore::game::bl1e
