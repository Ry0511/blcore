#include "blcore/pch.h"

#include "blcore/game/game.h"
#include "blcore/api/memory.h"
#include "blcore/util/logging.h"

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

void* get_gmalloc() {
    void** address = blcore::game::globals().gmalloc;
    return (address != nullptr) ? *address : nullptr;
}

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | EXPORTS |
////////////////////////////////////////////////////////////////////////////////

BLCORE_API_FN(void*, blcore_malloc, std::size_t size, std::uint32_t alignment) {
    void* gmalloc = get_gmalloc();
    if (gmalloc == nullptr) {
        BLCORE_ERROR("GMalloc is null, can't malloc {}", size);
        return nullptr;
    }
    return blcore::game::malloc(gmalloc, size, alignment);
}

BLCORE_API_FN(void*, blcore_realloc, void* original, std::size_t size, std::uint32_t alignment) {
    void* gmalloc = get_gmalloc();
    if (gmalloc == nullptr) {
        BLCORE_ERROR("GMalloc is null, can't realloc {}", size);
        return nullptr;
    }
    return blcore::game::realloc(gmalloc, original, size, alignment);
}

BLCORE_API_FN(void, blcore_free, void* data) {
    if (data == nullptr) {
        return;
    }

    void* gmalloc = get_gmalloc();
    if (gmalloc == nullptr) {
        BLCORE_ERROR("GMalloc is null, can't free {} ( how did you get here? )", data);
        return;
    }
    blcore::game::free(gmalloc, data);
}
