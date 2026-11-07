#ifndef BLCORE_UE3_UOBJECTPROPERTY_H
#define BLCORE_UE3_UOBJECTPROPERTY_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/layout.h"
#include "blcore/ue3/uproperty.h"

namespace blcore::ue3 {

struct UObjectProperty : UProperty {
    BLCORE_MAPPED_CLASS(UObjectProperty)

    BLCORE_UE3_FIELD(PropertyClass)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UOBJECTPROPERTY_H
