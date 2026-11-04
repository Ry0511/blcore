#ifndef BLCORE_UE3_FNAME_H
#define BLCORE_UE3_FNAME_H

#include "blcore/blcore.h"

namespace blcore::ue3 {

inline constexpr size_t NAME_SIZE = 1024;

#pragma pack(push, 4)

struct FName {
    int32_t Index{0};
    int32_t Number{0};
};

#pragma pack(pop)

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_FNAME_H
