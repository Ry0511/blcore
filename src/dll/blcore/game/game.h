#ifndef BLCORE_GAME_GAME_H
#define BLCORE_GAME_GAME_H

#include "blcore/ue3/tarray.h"

#include <cstddef>

namespace blcore::game {

struct Globals {
    ue3::TArray<void*>* gobjects{nullptr};
    void** gnames{nullptr};
    void** gmalloc{nullptr};
    void** gnatives{nullptr};
};

void find_globals(Globals& out);

void init_globals();
const Globals& globals();

void* malloc(void* gmalloc, std::size_t size);
void* realloc(void* gmalloc, void* original, std::size_t size);
void free(void* gmalloc, void* data);

}  // namespace blcore::game

#endif  // BLCORE_GAME_GAME_H
