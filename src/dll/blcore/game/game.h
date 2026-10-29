#ifndef BLCORE_GAME_GAME_H
#define BLCORE_GAME_GAME_H

#include "blcore/ue3/tarray.h"

#include <cstddef>

namespace blcore::game {

struct Globals {
    ue3::TArray<void*>* gobjects{nullptr};  // TArray<UObject*> UObject::GObjObjects
    void** gnames{nullptr};                 // TArray<FNameEntry*> FName::Names
    void** gmalloc{nullptr};                // FMalloc* GMalloc
    void** gnatives{nullptr};               // Native GNatives[EX_Max]
};

void find_globals(Globals& out);

void* malloc(void* gmalloc, std::size_t size);
void* realloc(void* gmalloc, void* original, std::size_t size);
void free(void* gmalloc, void* data);

}  // namespace blcore::game

#endif  // BLCORE_GAME_GAME_H
