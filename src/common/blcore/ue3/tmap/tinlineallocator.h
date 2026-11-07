#ifndef BLCORE_UE3_TMAP_TINLINEALLOCATOR_H
#define BLCORE_UE3_TMAP_TINLINEALLOCATOR_H

#include "blcore/blcore.h"

#include <array>

namespace blcore::ue3 {

#pragma pack(push, 4)

template <typename T, size_t N>
struct TInlineAllocator {
    std::array<T, N> InlineData{};
    T* SecondaryData{nullptr};

    template <typename Self>
    [[nodiscard]] auto* data(this Self& self) {
        return (self.SecondaryData != nullptr) ? self.SecondaryData : self.InlineData.data();
    }
};

#pragma pack(pop)

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_TMAP_TINLINEALLOCATOR_H
