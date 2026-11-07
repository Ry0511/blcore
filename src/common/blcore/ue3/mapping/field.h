#ifndef BLCORE_UE3_MAPPING_FIELD_H
#define BLCORE_UE3_MAPPING_FIELD_H

#include "blcore/blcore.h"

#include <type_traits>

namespace blcore::ue3 {

template <typename T, size_t Offset>
struct Field {
    using type = T;
    static constexpr size_t offset = Offset;
};

template <typename T, typename Self>
[[nodiscard]] auto& field(Self* self, size_t offset) {
    using Ptr = std::conditional_t<std::is_const_v<Self>, const T*, T*>;
    return *reinterpret_cast<Ptr>(reinterpret_cast<uintptr_t>(self) + offset);
}

}  // namespace blcore::ue3

// NOLINTBEGIN(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)

#define BLCORE_MAPPED_CLASS(cls)               \
   public:                                     \
    using layout_type = ::blcore::layout::cls; \
    cls() = delete;                            \
    cls(const cls&) = delete;                  \
    cls(cls&&) = delete;                       \
    cls& operator=(const cls&) = delete;       \
    cls& operator=(cls&&) = delete;            \
    ~cls() = delete;

#define BLCORE_UE3_FIELD(name)                                           \
    template <typename Self, typename Layout = layout_type>              \
    requires(requires { typename Layout::name; })                        \
    [[nodiscard]] auto& name(this Self& self) {                          \
        using F = typename Layout::name;                                 \
        return ::blcore::ue3::field<typename F::type>(&self, F::offset); \
    }

// NOLINTEND(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)

#endif  // BLCORE_UE3_MAPPING_FIELD_H
