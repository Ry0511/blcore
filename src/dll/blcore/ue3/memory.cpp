#include "blcore/pch.h"

#include "blcore/api/memory.h"
#include "blcore/game/game.h"
#include "blcore/util/logging.h"

namespace {

void* get_gmalloc() {
    void** address = blcore::game::current().globals().gmalloc;
    return (address != nullptr) ? *address : nullptr;
}

}  // namespace

BLCORE_API_FN(void*, blcore_malloc, size_t size, uint32_t alignment) {
    void* gmalloc = get_gmalloc();
    if (gmalloc == nullptr) {
        BLCORE_ERROR("GMalloc is null, can't malloc {}", size);
        return nullptr;
    }
    return blcore::game::current().malloc(gmalloc, size, alignment);
}

BLCORE_API_FN(void*, blcore_realloc, void* original, size_t size, uint32_t alignment) {
    void* gmalloc = get_gmalloc();
    if (gmalloc == nullptr) {
        BLCORE_ERROR("GMalloc is null, can't realloc {}", size);
        return nullptr;
    }
    return blcore::game::current().realloc(gmalloc, original, size, alignment);
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
    blcore::game::current().free(gmalloc, data);
}
