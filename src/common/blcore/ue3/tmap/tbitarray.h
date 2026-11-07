#ifndef BLCORE_UE3_TMAP_TBITARRAY_H
#define BLCORE_UE3_TMAP_TBITARRAY_H

#include "blcore/blcore.h"

#include <array>

namespace blcore::ue3 {

#pragma pack(push, 4)

struct TBitArray {
    std::array<uint32_t, 4> InlineData{};
    uint32_t* SecondaryData{nullptr};
    int32_t NumBits{0};
    int32_t MaxBits{0};

    template <typename Self>
    [[nodiscard]] auto* words(this Self& self) {
        return (self.SecondaryData != nullptr) ? self.SecondaryData : self.InlineData.data();
    }

    [[nodiscard]] bool get(int32_t index) const {
        return (words()[index / 32] & (1U << (index % 32))) != 0;
    }

    void set(int32_t index, bool value) {
        const uint32_t mask = 1U << (index % 32);
        uint32_t& word = words()[index / 32];
        word = value ? (word | mask) : (word & ~mask);
    }
};

#pragma pack(pop)

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_TMAP_TBITARRAY_H
