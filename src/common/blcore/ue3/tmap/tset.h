#ifndef BLCORE_UE3_TMAP_TSET_H
#define BLCORE_UE3_TMAP_TSET_H

#include "blcore/blcore.h"
#include "blcore/ue3/tmap/tinlineallocator.h"
#include "blcore/ue3/tmap/tsparsearray.h"

namespace blcore::ue3 {

#pragma pack(push, 4)

template <typename T>
struct TSet {
    struct FElement {
        T Value;
        int32_t HashNextId;
        int32_t HashIndex;
    };

    using ElementArray = TSparseArray<FElement>;

    ElementArray Elements;
    TInlineAllocator<int32_t, 1> Hash;
    int32_t HashSize{0};

    class Iterator {
       public:
        explicit Iterator(ElementArray::Iterator it) : m_It{it} {}

        T& operator*() const {
            return (*m_It).Value;
        }

        Iterator& operator++() {
            ++m_It;
            return *this;
        }

        bool operator==(const Iterator& other) const = default;

       private:
        ElementArray::Iterator m_It;
    };

    [[nodiscard]] int32_t max_index() const { return Elements.max_index(); }
    [[nodiscard]] size_t size() const { return Elements.size(); }
    [[nodiscard]] bool is_allocated(int32_t index) const { return Elements.is_allocated(index); }
    T& operator[](int32_t index) const { return Elements[index].Value; }

    void remove(int32_t index) {
        const FElement& removed = Elements[index];
        if (HashSize > 0) {
            int32_t* next = &Hash.data()[removed.HashIndex & (HashSize - 1)];
            while (*next != INDEX_NONE) {
                if (*next == index) {
                    *next = removed.HashNextId;
                    break;
                }
                next = &Elements[*next].HashNextId;
            }
        }
        Elements.remove(index);
    }

    [[nodiscard]] Iterator begin() const { return Iterator{Elements.begin()}; }
    [[nodiscard]] Iterator end() const { return Iterator{Elements.end()}; }
};

#pragma pack(pop)

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_TMAP_TSET_H
