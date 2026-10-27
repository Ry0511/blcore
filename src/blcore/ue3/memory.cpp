#include "blcore/pch.h"

#include "blcore/game/game.h"
#include "blcore/ue3/globals.h"
#include "blcore/ue3/memory.h"
#include "blcore/util/logging.h"

namespace blcore::ue3::memory {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

void* gmalloc() {
    void** address = found_globals().gmalloc;
    return (address != nullptr) ? *address : nullptr;
}

}  // namespace

}  // namespace blcore::ue3::memory

////////////////////////////////////////////////////////////////////////////////
// | EXPORTS |
////////////////////////////////////////////////////////////////////////////////

BLCORE_API_FN(void*, blcore_malloc, std::size_t size) {
    void* gmalloc = blcore::ue3::memory::gmalloc();
    if (gmalloc == nullptr) {
        BLCORE_ERROR("GMalloc is null, can't malloc {}", size);
        return nullptr;
    }
    return blcore::game::malloc(gmalloc, size);
}

BLCORE_API_FN(void*, blcore_realloc, void* original, std::size_t size) {
    void* gmalloc = blcore::ue3::memory::gmalloc();
    if (gmalloc == nullptr) {
        BLCORE_ERROR("GMalloc is null, can't realloc {}", size);
        return nullptr;
    }
    return blcore::game::realloc(gmalloc, original, size);
}

BLCORE_API_FN(void, blcore_free, void* data) {
    if (data == nullptr) {
        return;
    }

    void* gmalloc = blcore::ue3::memory::gmalloc();
    if (gmalloc == nullptr) {
        BLCORE_ERROR("GMalloc is null, can't free {} ( how did you get here? )", data);
        return;
    }
    blcore::game::free(gmalloc, data);
}
