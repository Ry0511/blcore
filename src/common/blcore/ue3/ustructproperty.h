#ifndef BLCORE_UE3_USTRUCTPROPERTY_H
#define BLCORE_UE3_USTRUCTPROPERTY_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/layout.h"
#include "blcore/ue3/uproperty.h"

namespace blcore::ue3 {

struct UStructProperty : UProperty {
    BLCORE_MAPPED_CLASS(UStructProperty)

    BLCORE_UE3_FIELD(Struct)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_USTRUCTPROPERTY_H
