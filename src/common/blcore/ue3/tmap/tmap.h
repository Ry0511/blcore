#ifndef BLCORE_UE3_TMAP_TMAP_H
#define BLCORE_UE3_TMAP_TMAP_H

#include "blcore/blcore.h"
#include "blcore/ue3/tmap/tset.h"

namespace blcore::ue3 {

#pragma pack(push, 4)

template <typename K, typename V>
struct TMap {
    struct FPair {
        K Key;
        V Value;
    };

    TSet<FPair> Pairs;

    [[nodiscard]] size_t size() const { return Pairs.size(); }
    [[nodiscard]] auto begin() const { return Pairs.begin(); }
    [[nodiscard]] auto end() const { return Pairs.end(); }
};

#pragma pack(pop)

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_TMAP_TMAP_H
