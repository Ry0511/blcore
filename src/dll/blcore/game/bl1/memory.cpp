#include "blcore/pch.h"

#include "blcore/game/bl1/game_impl.h"

namespace blcore::game::bl1 {

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

void* GameImpl::malloc(void* gmalloc, size_t size, uint32_t alignment) const {
    auto* self = static_cast<FMalloc*>(gmalloc);
    return self->vtable->malloc(self, static_cast<uint32_t>(size), alignment);
}

void* GameImpl::realloc(
    void* gmalloc,  // NOLINT(bugprone-easily-swappable-parameters)
    void* original,
    size_t size,
    uint32_t alignment
) const {
    auto* self = static_cast<FMalloc*>(gmalloc);
    return self->vtable->realloc(self, original, static_cast<uint32_t>(size), alignment);
}

void GameImpl::free(
    void* gmalloc,  // NOLINT(bugprone-easily-swappable-parameters)
    void* data
) const {
    auto* self = static_cast<FMalloc*>(gmalloc);
    self->vtable->free(self, data);
}

}  // namespace blcore::game::bl1
