#ifndef BLCORE_UE3_UPROP_UARRAYPROPERTY_H
#define BLCORE_UE3_UPROP_UARRAYPROPERTY_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/mapping/field.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/mapping/layout.h"
#include "blcore/ue3/uprop/uproperty.h"

namespace blcore::ue3 {

struct UArrayProperty : UProperty {
    BLCORE_MAPPED_CLASS(UArrayProperty)

    BLCORE_UE3_FIELD(Inner)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UPROP_UARRAYPROPERTY_H
