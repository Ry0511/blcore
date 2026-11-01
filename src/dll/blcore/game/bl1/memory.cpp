#include "blcore/pch.h"

#ifdef WILLOW

#include "blcore/game/game.h"

namespace blcore::game {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

struct FMalloc;

struct FMallocVTable {
    void* exec;
    void*(__thiscall* malloc)(FMalloc* self, uint32_t count, uint32_t alignment);
    void*(__thiscall* realloc)(FMalloc* self, void* original, uint32_t count, uint32_t alignment);
    void(__thiscall* free)(FMalloc* self, void* original);
};

struct FMalloc {
    FMallocVTable* vtable;
};

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////


void* malloc(void* gmalloc, size_t size, uint32_t alignment) {
    auto* self = static_cast<FMalloc*>(gmalloc);
    return self->vtable->malloc(self, static_cast<uint32_t>(size), alignment);
}

void* realloc(
    void* gmalloc,  // NOLINT(bugprone-easily-swappable-parameters)
    void* original,
    size_t size,
    uint32_t alignment
) {
    auto* self = static_cast<FMalloc*>(gmalloc);
    return self->vtable->realloc(self, original, static_cast<uint32_t>(size), alignment);
}

void free(
    void* gmalloc,  // NOLINT(bugprone-easily-swappable-parameters)
    void* data
) {
    auto* self = static_cast<FMalloc*>(gmalloc);
    self->vtable->free(self, data);
}

}  // namespace blcore::game

#endif  // WILLOW
