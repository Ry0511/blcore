#ifndef BLCORE_UTIL_HOOK_H
#define BLCORE_UTIL_HOOK_H

#include "blcore/api/hook.h"

#include <string_view>
#include <type_traits>

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

namespace blcore::hook {

template <typename Fn>
concept FunctionPointer = std::is_pointer_v<Fn> && std::is_function_v<std::remove_pointer_t<Fn>>;

template <FunctionPointer Fn>
bool create(void* target, Fn detour, Fn* original = nullptr) {
    return blcore_hook_create(
        target,
        reinterpret_cast<void*>(detour),
        reinterpret_cast<void**>(original)
    );
}

template <FunctionPointer Fn>
bool create_export(
    std::wstring_view module,
    std::string_view name,
    Fn detour,
    Fn* original = nullptr,
    void** out_target = nullptr
) {
    return blcore_hook_create_export(
        module.data(),
        module.size(),
        name.data(),
        name.size(),
        reinterpret_cast<void*>(detour),
        reinterpret_cast<void**>(original),
        out_target
    );
}

inline bool remove(void* target) {
    return blcore_hook_remove(target);
}

inline bool enable(void* target) {
    return blcore_hook_enable(target);
}

inline bool disable(void* target) {
    return blcore_hook_disable(target);
}

template <FunctionPointer Fn>
bool install(void* target, Fn detour, Fn* original = nullptr) {
    if (!create(target, detour, original)) {
        return false;
    }

    if (!enable(target)) {
        remove(target);
        if (original != nullptr) {
            *original = nullptr;
        }
        return false;
    }

    return true;
}

}  // namespace blcore::hook

#endif  // BLCORE_UTIL_HOOK_H
