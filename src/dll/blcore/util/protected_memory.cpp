#include "blcore/pch.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "blcore/api/protected_memory.h"
#include "blcore/util/logging.h"

////////////////////////////////////////////////////////////////////////////////
// | EXPORTS |
////////////////////////////////////////////////////////////////////////////////

BLCORE_API_FN(
    blcore::ApiResult,
    blcore_write_protected_memory,
    void* address,
    const uint8_t* bytes,
    size_t size
) {
    if (address == nullptr || bytes == nullptr || size == 0) {
        BLCORE_ERROR("Can't write to {}: null address or no bytes", address);
        return blcore::API_FAIL;
    }

    DWORD old_protect = 0;
    if (VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &old_protect) == FALSE) {
        BLCORE_ERROR("Can't write to {}: VirtualProtect failed ({})", address, GetLastError());
        return blcore::API_FAIL;
    }

    std::memcpy(address, bytes, size);

    DWORD unused = 0;
    VirtualProtect(address, size, old_protect, &unused);
    FlushInstructionCache(GetCurrentProcess(), address, size);

    BLCORE_INFO("Wrote {} bytes at {}", size, address);
    return blcore::API_OK;
}
