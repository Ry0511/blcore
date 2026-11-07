#ifndef BLCORE_UE3_UCLASS_H
#define BLCORE_UE3_UCLASS_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/layout.h"
#include "blcore/ue3/ustate.h"

namespace blcore::ue3 {

struct UClass : UState {
    BLCORE_MAPPED_CLASS(UClass)

    BLCORE_UE3_FIELD(ClassFlags)
    BLCORE_UE3_FIELD(ClassCastFlags)
    BLCORE_UE3_FIELD(ClassWithin)
    BLCORE_UE3_FIELD(ClassDefaultObject)
    BLCORE_UE3_FIELD(ClassConstructor)
    BLCORE_UE3_FIELD(ComponentNameToDefaultObjectMap)
    BLCORE_UE3_FIELD(Interfaces)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UCLASS_H
