#include "blcore/pch.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include <MinHook.h>

#include "blcore/util/common.h"
#include "blcore/util/hook.h"
#include "blcore/util/logging.h"

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

using MinHookFn = MH_STATUS(WINAPI*)(LPVOID target);

blcore::ApiResult apply(std::string_view action, MinHookFn fn, void* target) {
    if (target == nullptr) {
        BLCORE_ERROR("Can't {} a hook with a null target", action);
        return blcore::API_FAIL;
    }

    const MH_STATUS status = fn(target);
    if (status != MH_OK) {
        BLCORE_ERROR("Failed to {} hook at {}: {}", action, target, MH_StatusToString(status));
        return blcore::API_FAIL;
    }

    return blcore::API_OK;
}

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | EXPORTS |
////////////////////////////////////////////////////////////////////////////////

BLCORE_API_FN(blcore::ApiResult, blcore_hook_create, void* target, void* detour, void** original) {
    if (target == nullptr || detour == nullptr) {
        BLCORE_ERROR("Can't create a hook with a null target or detour");
        return blcore::API_FAIL;
    }

    const MH_STATUS status = MH_CreateHook(target, detour, original);
    if (status != MH_OK) {
        BLCORE_ERROR("Failed to create hook at {}: {}", target, MH_StatusToString(status));
        return blcore::API_FAIL;
    }

    return blcore::API_OK;
}

BLCORE_API_FN(
    blcore::ApiResult,
    blcore_hook_create_export,
    const wchar_t* module,
    std::size_t module_len,
    const char* name,
    std::size_t name_len,
    void* detour,
    void** original,  // NOLINT(bugprone-easily-swappable-parameters)
    void** out_target
) {
    if (module == nullptr || name == nullptr || detour == nullptr) {
        BLCORE_ERROR("Can't create an export hook with a null module, name or detour");
        return blcore::API_FAIL;
    }

    const std::wstring module_str{module, module_len};
    const std::string name_str{name, name_len};

    void* target = nullptr;
    const MH_STATUS status = MH_CreateHookApiEx(
        module_str.c_str(),
        name_str.c_str(),
        detour,
        original,
        &target
    );

    if (status != MH_OK) {
        BLCORE_ERROR(
            "Failed to create hook on {}!{}: {}",
            blcore::util::narrow(module_str),
            name_str,
            MH_StatusToString(status)
        );
        return blcore::API_FAIL;
    }

    if (out_target != nullptr) {
        *out_target = target;
    }
    return blcore::API_OK;
}

BLCORE_API_FN(blcore::ApiResult, blcore_hook_remove, void* target) {
    return apply("remove", &MH_RemoveHook, target);
}

BLCORE_API_FN(blcore::ApiResult, blcore_hook_enable, void* target) {
    return apply("enable", &MH_EnableHook, target);
}

BLCORE_API_FN(blcore::ApiResult, blcore_hook_disable, void* target) {
    return apply("disable", &MH_DisableHook, target);
}
