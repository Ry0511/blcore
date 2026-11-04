#ifndef BLCORE_API_HOOK_H
#define BLCORE_API_HOOK_H

#include "blcore/api/api.h"
#include "blcore/blcore.h"

// hook an arbitrary function
BLCORE_API_FN(blcore::ApiResult, blcore_hook_create, void* target, void* detour, void** original);

// hook an exported module function by name
BLCORE_API_FN(
    blcore::ApiResult,
    blcore_hook_create_export,
    const wchar_t* module,
    size_t module_len,
    const char* name,
    size_t name_len,
    void* detour,
    void** original,
    void** out_target
);

BLCORE_API_FN(blcore::ApiResult, blcore_hook_remove, void* target);
BLCORE_API_FN(blcore::ApiResult, blcore_hook_enable, void* target);
BLCORE_API_FN(blcore::ApiResult, blcore_hook_disable, void* target);

#endif  // BLCORE_API_HOOK_H
