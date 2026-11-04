#ifndef BLCORE_UE3_IMPL_BL1_CORE_H
#define BLCORE_UE3_IMPL_BL1_CORE_H

#include "blcore/blcore.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/tarray.h"

namespace blcore::bl1 {

using ue3::Field;

struct UObject {
    using VfTableObject   = Field<uintptr_t, 0x00>;
    using InternalIndex   = Field<int32_t, 0x04>;
    using ObjectFlags     = Field<uint64_t, 0x08>;
    using HashNext        = Field<ue3::UObject*, 0x10>;
    using HashOuterNext   = Field<ue3::UObject*, 0x14>;
    using StateFrame      = Field<void*, 0x18>;
    using Linker          = Field<ue3::UObject*, 0x1C>;
    using LinkerIndex     = Field<int32_t, 0x20>;
    using NetIndex        = Field<int32_t, 0x24>;
    using Outer           = Field<ue3::UObject*, 0x28>;
    using Name            = Field<ue3::FName, 0x2C>;
    using Class           = Field<ue3::UClass*, 0x34>;
    using ObjectArchetype = Field<ue3::UObject*, 0x38>;
};

struct UField {
    using SuperField = Field<ue3::UField*, 0x3C>;
    using Next       = Field<ue3::UField*, 0x40>;
};

struct UStruct {
    using SuperField     = Field<ue3::UStruct*, 0x3C>;
    using ScriptText     = Field<void*, 0x44>;
    using CppText        = Field<void*, 0x48>;
    using Children       = Field<ue3::UField*, 0x4C>;
    using PropertiesSize = Field<int32_t, 0x50>;
    using Script         = Field<ue3::TArray<uint8_t>, 0x54>;
    using PropertyLink   = Field<ue3::UProperty*, 0x70>;
};

struct UFunction {
    using FunctionFlags           = Field<uint32_t, 0x94>;
    using iNative                 = Field<uint16_t, 0x98>;
    using RepOffset               = Field<uint16_t, 0x9A>;
    using FriendlyName            = Field<ue3::FName, 0x9C>;
    using OperPrecedence          = Field<uint8_t, 0xA4>;
    using NumParms                = Field<uint8_t, 0xA5>;
    using ParmsSize               = Field<uint16_t, 0xA6>;
    using ReturnValueOffset       = Field<uint16_t, 0xA8>;
    using FirstStructWithDefaults = Field<ue3::UStruct*, 0xAC>;
    using Func                    = Field<void*, 0xB0>;
};

struct UClass {
    using ClassFlags         = Field<uint32_t, 0xE8>;
    using ClassCastFlags     = Field<uint32_t, 0xEC>;
    using ClassDefaultObject = Field<ue3::UObject*, 0x154>;
    using ClassConstructor   = Field<void*, 0x158>;
};

struct UProperty {
    using ArrayDim         = Field<int32_t, 0x44>;
    using ElementSize      = Field<int32_t, 0x48>;
    using PropertyFlags    = Field<uint64_t, 0x4C>;
    using Offset           = Field<int32_t, 0x64>;
    using PropertyLinkNext = Field<ue3::UProperty*, 0x68>;
};

struct UEnum {
    using Names = Field<ue3::TArray<ue3::FName>, 0x44>;
};

struct UPackage {
    using PackageFlags = Field<uint32_t, 0x9C>;
};

struct FNameEntry {
    using Flags    = Field<uint64_t, 0x00>;
    using Index    = Field<int32_t, 0x08>;
    using HashNext = Field<ue3::FNameEntry*, 0x0C>;
    using AnsiName = Field<char[ue3::NAME_SIZE], 0x10>;
    using UniName  = Field<wchar_t[ue3::NAME_SIZE], 0x10>;
};

}  // namespace blcore::bl1

#endif  // BLCORE_UE3_IMPL_BL1_CORE_H
