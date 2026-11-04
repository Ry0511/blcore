#ifndef BLCORE_UE3_CORE_H
#define BLCORE_UE3_CORE_H

#include "blcore/ue3/bl1/core.h"
#include "blcore/ue3/bl1e/core.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/layout.h"

namespace blcore::ue3 {

struct UObject {
    BLCORE_MAPPED_CLASS(UObject)

    BLCORE_UE3_FIELD(VfTableObject)
    BLCORE_UE3_FIELD(InternalIndex)
    BLCORE_UE3_FIELD(ObjectFlags)
    BLCORE_UE3_FIELD(HashNext)
    BLCORE_UE3_FIELD(HashOuterNext)
    BLCORE_UE3_FIELD(StateFrame)
    BLCORE_UE3_FIELD(Linker)
    BLCORE_UE3_FIELD(LinkerIndex)
    BLCORE_UE3_FIELD(NetIndex)
    BLCORE_UE3_FIELD(Outer)
    BLCORE_UE3_FIELD(Name)
    BLCORE_UE3_FIELD(Class)
    BLCORE_UE3_FIELD(ObjectArchetype)
};

struct UField : UObject {
    BLCORE_MAPPED_CLASS(UField)
};

struct UStruct : UField {
    BLCORE_MAPPED_CLASS(UStruct)
};

struct UState : UStruct {
    BLCORE_MAPPED_CLASS(UState)
};

struct UClass : UState {
    BLCORE_MAPPED_CLASS(UClass)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_CORE_H
