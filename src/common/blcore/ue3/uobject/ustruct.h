#ifndef BLCORE_UE3_UOBJECT_USTRUCT_H
#define BLCORE_UE3_UOBJECT_USTRUCT_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/mapping/field.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/mapping/layout.h"
#include "blcore/ue3/tarray.h"
#include "blcore/ue3/uobject/ufield.h"

namespace blcore::ue3 {

struct UStruct : UField {
    BLCORE_MAPPED_CLASS(UStruct)

    BLCORE_UE3_FIELD(SuperField)
    BLCORE_UE3_FIELD(ScriptText)
    BLCORE_UE3_FIELD(Children)
    BLCORE_UE3_FIELD(PropertiesSize)
    BLCORE_UE3_FIELD(PropertyLink)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UOBJECT_USTRUCT_H
