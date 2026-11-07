#ifndef BLCORE_UE3_MAPPING_VFUNC_H
#define BLCORE_UE3_MAPPING_VFUNC_H

#include "blcore/blcore.h"

#include <utility>

namespace blcore::ue3 {

template <typename Sig, size_t VtableIndex = 0>
struct VFunc;

template <typename R, typename... Args, size_t VtableIndex>
struct VFunc<R(Args...), VtableIndex> {
    using type = R(Args...);
    static constexpr size_t vtable_index = VtableIndex;

    static R invoke(const void* self, size_t index, Args... args) {
        using Fn = R(__thiscall*)(const void*, Args...);
        void* const* vftable = *static_cast<void* const* const*>(self);
        return reinterpret_cast<Fn>(vftable[index])(self, args...);
    }
};

template <typename Sig, typename... CallArgs>
decltype(auto) invoke_virtual(const void* self, size_t vtable_index, CallArgs&&... args) {
    return VFunc<Sig>::invoke(self, vtable_index, std::forward<CallArgs>(args)...);
}

}  // namespace blcore::ue3

// NOLINTBEGIN(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)

#define BLCORE_UE3_VFUNC(name)                                                     \
    template <typename Self, typename Layout = layout_type, typename... CallArgs>  \
    requires(requires { typename Layout::name; })                                  \
    decltype(auto) name(this Self& self, CallArgs&&... args) {                     \
        using F = typename Layout::name;                                           \
        return F::invoke(&self, F::vtable_index, std::forward<CallArgs>(args)...); \
    }

// NOLINTEND(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)

#endif  // BLCORE_UE3_MAPPING_VFUNC_H
