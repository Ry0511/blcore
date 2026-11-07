#ifndef BLCORE_UE3_UOBJECT_UOBJECT_H
#define BLCORE_UE3_UOBJECT_UOBJECT_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/mapping/field.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/mapping/layout.h"
#include "blcore/ue3/mapping/vfunc.h"

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

    BLCORE_UE3_VFUNC(Rename)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UOBJECT_UOBJECT_H
