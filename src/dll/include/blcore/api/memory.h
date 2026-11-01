#ifndef BLCORE_API_MEMORY_H
#define BLCORE_API_MEMORY_H

#include "blcore/api/api.h"

#include <cstddef>
#include <cstdint>

BLCORE_API_FN(void*, blcore_malloc, std::size_t size, std::uint32_t alignment);
BLCORE_API_FN(void*, blcore_realloc, void* original, std::size_t size, std::uint32_t alignment);
BLCORE_API_FN(void, blcore_free, void* data);

#endif  // BLCORE_API_MEMORY_H
