#ifndef BLCORE_ENGINE_MEMORY_H
#define BLCORE_ENGINE_MEMORY_H

#include "blcore/api/memory.h"

#include <cstddef>

namespace blcore::engine {

inline void* malloc(std::size_t size) {
    return blcore_malloc(size);
}

inline void* realloc(void* original, std::size_t size) {
    return blcore_realloc(original, size);
}

inline void free(void* data) {
    blcore_free(data);
}

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_MEMORY_H
