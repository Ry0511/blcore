#ifndef BLCORE_UE3_TARRAY_H
#define BLCORE_UE3_TARRAY_H

#include "blcore/blcore.h"

#include <span>

namespace blcore::ue3 {

#pragma pack(push, 4)

template <typename T>
struct TArray {
    T* Data{nullptr};
    int32_t ArrayNum{0};
    int32_t ArrayMax{0};

    [[nodiscard]] std::span<T> span() const {
        return {Data, static_cast<size_t>(ArrayNum)};
    }

    [[nodiscard]] size_t size() const {
        return static_cast<size_t>(ArrayNum);
    }

    [[nodiscard]] auto begin() const {
        return span().begin();
    }

    [[nodiscard]] auto end() const {
        return span().end();
    }
};

#pragma pack(pop)

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_TARRAY_H
