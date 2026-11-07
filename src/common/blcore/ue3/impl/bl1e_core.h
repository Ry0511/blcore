#ifndef BLCORE_UE3_IMPL_BL1E_CORE_H
#define BLCORE_UE3_IMPL_BL1E_CORE_H

#include "blcore/blcore.h"
#include "blcore/ue3/mapping/field.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/tarray.h"
#include "blcore/ue3/tmap/tmap.h"
#include "blcore/ue3/uobject/fimplementedinterface.h"

namespace blcore::bl1e {

using ue3::Field;

struct UObject {
    using VfTableObject   = Field<uintptr_t, 0x00>;
    using HashNext        = Field<ue3::UObject*, 0x08>;
    using ObjectFlags     = Field<uint64_t, 0x10>;
    using HashOuterNext   = Field<ue3::UObject*, 0x18>;
    using StateFrame      = Field<void*, 0x20>;
    using Linker          = Field<ue3::UObject*, 0x28>;
    using LinkerIndex     = Field<int32_t, 0x30>;
    using InternalIndex   = Field<int32_t, 0x38>;
    using NetIndex        = Field<int32_t, 0x3C>;
    using Outer           = Field<ue3::UObject*, 0x40>;
    using Name            = Field<ue3::FName, 0x48>;
    using Class           = Field<ue3::UClass*, 0x50>;
    using ObjectArchetype = Field<ue3::UObject*, 0x58>;
};

struct UField {
    using Next = Field<ue3::UField*, 0x60>;
};

struct UStruct {
    using ScriptText     = Field<void*, 0x68>;
    using SuperField     = Field<ue3::UStruct*, 0x78>;
    using Children       = Field<ue3::UField*, 0x80>;
    using PropertiesSize = Field<uint16_t, 0x88>;
    using PropertyLink   = Field<ue3::UProperty*, 0xB0>;
};

struct UFunction {
    using FunctionFlags     = Field<uint32_t, 0xD0>;
    using iNative           = Field<uint16_t, 0xD4>;
    using NumParms          = Field<uint8_t, 0xE1>;
    using ParmsSize         = Field<uint16_t, 0xE2>;
    using ReturnValueOffset = Field<uint16_t, 0xE4>;
};

struct UState {
    using FuncMap = Field<ue3::TMap<ue3::FName, ue3::UFunction*>, 0xDC>;
};

struct UClass {
    using ClassFlags                      = Field<uint32_t, 0x124>;
    using ClassWithin                     = Field<ue3::UClass*, 0x130>;
    using ClassDefaultObject              = Field<ue3::UObject*, 0x1D4>;
    using ComponentNameToDefaultObjectMap = Field<ue3::TMap<ue3::FName, ue3::UObject*>, 0x1F4>;
    using Interfaces                      = Field<ue3::TArray<ue3::FImplementedInterface>, 0x23C>;
};

struct UProperty {
    using ArrayDim         = Field<int32_t, 0x68>;
    using ElementSize      = Field<int32_t, 0x6C>;
    using PropertyFlags    = Field<uint64_t, 0x70>;
    using Offset           = Field<int32_t, 0x8C>;
    using PropertyLinkNext = Field<ue3::UProperty*, 0x90>;
};

struct UObjectProperty {
    using PropertyClass = Field<ue3::UClass*, 0xB8>;
};

struct UArrayProperty {
    using Inner = Field<ue3::UProperty*, 0xB8>;
};

struct UStructProperty {
    using Struct = Field<ue3::UStruct*, 0xB8>;
};

struct UEnum {
    using Names = Field<ue3::TArray<ue3::FName>, 0x68>;
};

struct UPackage {
    using PackageFlags = Field<uint32_t, 0xCC>;
};

struct FNameEntry {
    using Index    = Field<int32_t, 0x08>;
    using AnsiName = Field<char[ue3::NAME_SIZE], 0x14>;
    using UniName  = Field<wchar_t[ue3::NAME_SIZE], 0x14>;
};

}  // namespace blcore::bl1e

#endif  // BLCORE_UE3_IMPL_BL1E_CORE_H
