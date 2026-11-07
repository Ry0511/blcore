#ifndef BLCORE_UE3_UPROP_UPROPERTY_H
#define BLCORE_UE3_UPROP_UPROPERTY_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/mapping/field.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/mapping/layout.h"
#include "blcore/ue3/uobject/ufield.h"

namespace blcore::ue3 {

struct UProperty : UField {
    BLCORE_MAPPED_CLASS(UProperty)

    BLCORE_UE3_FIELD(ArrayDim)
    BLCORE_UE3_FIELD(ElementSize)
    BLCORE_UE3_FIELD(PropertyFlags)
    BLCORE_UE3_FIELD(Offset)
    BLCORE_UE3_FIELD(PropertyLinkNext)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UPROP_UPROPERTY_H
