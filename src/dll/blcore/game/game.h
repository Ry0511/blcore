#ifndef BLCORE_GAME_GAME_H
#define BLCORE_GAME_GAME_H

#include "blcore/ue3/fwd.h"
#include "blcore/ue3/tarray.h"

#include <cstddef>
#include <cstdint>

namespace blcore::game {

struct Globals {
    ue3::TArray<ue3::UObject*>* gobjects{nullptr};
    void** gnames{nullptr};
    void** gmalloc{nullptr};
    void** gnatives{nullptr};
};

void find_globals(Globals& out);

void init_globals();
const Globals& globals();

void* malloc(void* gmalloc, std::size_t size, std::uint32_t alignment);
void* realloc(void* gmalloc, void* original, std::size_t size, std::uint32_t alignment);
void free(void* gmalloc, void* data);

}  // namespace blcore::game

#endif  // BLCORE_GAME_GAME_H
