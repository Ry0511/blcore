#ifndef BLCORE_GAME_GAME_H
#define BLCORE_GAME_GAME_H

#include "blcore/blcore.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/tarray.h"

namespace blcore::game {

struct Globals {
    ue3::TArray<ue3::UObject*>* gobjects{nullptr};
    ue3::TArray<ue3::FNameEntry*>* gnames{nullptr};
    void** gmalloc{nullptr};
    void** gnatives{nullptr};
};

void find_globals(Globals& out);

void init_globals();
const Globals& globals();

void* malloc(void* gmalloc, size_t size, uint32_t alignment);
void* realloc(void* gmalloc, void* original, size_t size, uint32_t alignment);
void free(void* gmalloc, void* data);

}  // namespace blcore::game

#endif  // BLCORE_GAME_GAME_H
