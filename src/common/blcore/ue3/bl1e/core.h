#ifndef BLCORE_UE3_BL1E_CORE_H
#define BLCORE_UE3_BL1E_CORE_H

#include "blcore/ue3/field.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/fwd.h"

#include <cstdint>

namespace blcore::bl1e {

using ue3::Field;

struct UObject {
    using VfTableObject = Field<uintptr_t, 0x00>;
    using HashNext = Field<ue3::UObject*, 0x08>;
    using ObjectFlags = Field<uint64_t, 0x10>;
    using HashOuterNext = Field<ue3::UObject*, 0x18>;
    using StateFrame = Field<void*, 0x20>;
    using Linker = Field<ue3::UObject*, 0x28>;
    using LinkerIndex = Field<int32_t, 0x30>;
    using InternalIndex = Field<int32_t, 0x38>;
    using NetIndex = Field<int32_t, 0x3C>;
    using Outer = Field<ue3::UObject*, 0x40>;
    using Name = Field<ue3::FName, 0x48>;
    using Class = Field<ue3::UClass*, 0x50>;
    using ObjectArchetype = Field<ue3::UObject*, 0x58>;
};

struct UField {};
struct UStruct {};
struct UState {};
struct UClass {};

}  // namespace blcore::bl1e

#endif  // BLCORE_UE3_BL1E_CORE_H
