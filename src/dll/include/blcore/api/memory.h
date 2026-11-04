#ifndef BLCORE_API_MEMORY_H
#define BLCORE_API_MEMORY_H

#include "blcore/api/api.h"
#include "blcore/blcore.h"

BLCORE_API_FN(void*, blcore_malloc, size_t size, uint32_t alignment);
BLCORE_API_FN(void*, blcore_realloc, void* original, size_t size, uint32_t alignment);
BLCORE_API_FN(void, blcore_free, void* data);

#endif  // BLCORE_API_MEMORY_H
