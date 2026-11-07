#ifndef BLCORE_UE3_UOBJECT_USTATE_H
#define BLCORE_UE3_UOBJECT_USTATE_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/layout.h"
#include "blcore/ue3/uobject/ustruct.h"

namespace blcore::ue3 {

struct UState : UStruct {
    BLCORE_MAPPED_CLASS(UState)

    BLCORE_UE3_FIELD(FuncMap)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UOBJECT_USTATE_H
