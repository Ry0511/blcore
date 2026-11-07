#ifndef BLCORE_UE3_TMAP_TSPARSEARRAY_H
#define BLCORE_UE3_TMAP_TSPARSEARRAY_H

#include "blcore/blcore.h"
#include "blcore/ue3/tarray.h"
#include "blcore/ue3/tmap/tbitarray.h"

namespace blcore::ue3 {

inline constexpr int32_t INDEX_NONE = -1;

#pragma pack(push, 4)

template <typename T>
struct TSparseArray {
    union FElementOrFreeListLink {
        T ElementData;
        int32_t NextFreeIndex;
    };

    TArray<FElementOrFreeListLink> Data;
    TBitArray AllocationFlags;
    int32_t FirstFreeIndex{0};
    int32_t NumFreeIndices{0};

    class Iterator {
       public:
        Iterator(const TSparseArray* array, int32_t index) : m_Array{array}, m_Index{index} {
            skip_free();
        }

        T& operator*() const {
            return (*m_Array)[m_Index];
        }

        Iterator& operator++() {
            ++m_Index;
            skip_free();
            return *this;
        }

        bool operator==(const Iterator& other) const = default;

       private:
        void skip_free() {
            while (m_Index < m_Array->max_index() && !m_Array->is_allocated(m_Index)) {
                ++m_Index;
            }
        }

        const TSparseArray* m_Array;
        int32_t m_Index;
    };

    [[nodiscard]] int32_t max_index() const { return Data.ArrayNum; }
    [[nodiscard]] size_t size() const { return static_cast<size_t>(Data.ArrayNum - NumFreeIndices); }

    [[nodiscard]] bool is_allocated(int32_t index) const {
        return index >= 0
               && index < Data.ArrayNum
               && AllocationFlags.get(index);
    }

    T& operator[](int32_t index) const {
        return Data.Data[index].ElementData;
    }

    void remove(int32_t index) {
        Data.Data[index].NextFreeIndex = (NumFreeIndices > 0) ? FirstFreeIndex : INDEX_NONE;
        FirstFreeIndex = index;
        ++NumFreeIndices;
        AllocationFlags.set(index, false);
    }

    [[nodiscard]] Iterator begin() const { return Iterator{this, 0}; }
    [[nodiscard]] Iterator end() const { return Iterator{this, Data.ArrayNum}; }
};

#pragma pack(pop)

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_TMAP_TSPARSEARRAY_H
