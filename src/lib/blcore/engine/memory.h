#ifndef BLCORE_ENGINE_MEMORY_H
#define BLCORE_ENGINE_MEMORY_H

#include "blcore/api/memory.h"

#include <cstddef>
#include <cstdint>

namespace blcore::engine {

// this is here for abi reasons, but BL1 and BL1E both ignore the alignment parameter and always
//  align GMalloc to 16
inline constexpr std::uint32_t DEFAULT_ALIGNMENT = 8;

inline void* malloc(std::size_t size, std::uint32_t alignment = DEFAULT_ALIGNMENT) {
    return blcore_malloc(size, alignment);
}

inline void* realloc(void* original, std::size_t size, std::uint32_t alignment = DEFAULT_ALIGNMENT) {
    return blcore_realloc(original, size, alignment);
}

inline void free(void* data) {
    blcore_free(data);
}

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_MEMORY_H
