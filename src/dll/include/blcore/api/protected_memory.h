#ifndef BLCORE_API_PROTECTED_MEMORY_H
#define BLCORE_API_PROTECTED_MEMORY_H

#include "blcore/api/api.h"
#include "blcore/blcore.h"

BLCORE_API_FN(
    blcore::ApiResult,
    blcore_write_protected_memory,
    void* address,
    const uint8_t* bytes,
    size_t size
);

#endif  // BLCORE_API_PROTECTED_MEMORY_H
