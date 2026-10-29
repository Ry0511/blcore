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
    void* Exec;
    void*(__thiscall* Malloc)(FMalloc* self, uint32_t count, uint32_t alignment);
    void*(__thiscall* Realloc)(FMalloc* self, void* original, uint32_t count, uint32_t alignment);
    void(__thiscall* Free)(FMalloc* self, void* original);
};

struct FMalloc {
    FMallocVTable* VTable;
};

// the engine ignores this value and always aligns to 16 for GMalloc
constexpr uint32_t DEFAULT_ALIGNMENT = 16;

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

void* malloc(void* gmalloc, size_t size) {
    auto* self = static_cast<FMalloc*>(gmalloc);
    return self->VTable->Malloc(self, static_cast<uint32_t>(size), DEFAULT_ALIGNMENT);
}

void* realloc(
    void* gmalloc,  // NOLINT(bugprone-easily-swappable-parameters)
    void* original,
    size_t size
) {
    auto* self = static_cast<FMalloc*>(gmalloc);
    return self->VTable->Realloc(self, original, static_cast<uint32_t>(size), DEFAULT_ALIGNMENT);
}

void free(
    void* gmalloc,  // NOLINT(bugprone-easily-swappable-parameters)
    void* data
) {
    auto* self = static_cast<FMalloc*>(gmalloc);
    self->VTable->Free(self, data);
}

}  // namespace blcore::game

#endif  // WILLOW
