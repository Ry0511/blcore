#ifndef BLCORE_UE3_BL1_CORE_H
#define BLCORE_UE3_BL1_CORE_H

#include "blcore/ue3/field.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/fwd.h"

#include <cstdint>

namespace blcore::bl1 {

using ue3::Field;

struct UObject {
    using VfTableObject = Field<uintptr_t, 0x00>;
    using InternalIndex = Field<int32_t, 0x04>;
    using ObjectFlags = Field<uint64_t, 0x08>;
    using HashNext = Field<ue3::UObject*, 0x10>;
    using HashOuterNext = Field<ue3::UObject*, 0x14>;
    using StateFrame = Field<void*, 0x18>;
    using Linker = Field<ue3::UObject*, 0x1C>;
    using LinkerIndex = Field<int32_t, 0x20>;
    using NetIndex = Field<int32_t, 0x24>;
    using Outer = Field<ue3::UObject*, 0x28>;
    using Name = Field<ue3::FName, 0x2C>;
    using Class = Field<ue3::UClass*, 0x34>;
    using ObjectArchetype = Field<ue3::UObject*, 0x38>;
};

struct UField {};
struct UStruct {};
struct UState {};
struct UClass {};

}  // namespace blcore::bl1

#endif  // BLCORE_UE3_BL1_CORE_H
