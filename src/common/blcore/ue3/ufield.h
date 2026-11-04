#ifndef BLCORE_UE3_UFIELD_H
#define BLCORE_UE3_UFIELD_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/layout.h"
#include "blcore/ue3/uobject.h"

namespace blcore::ue3 {

struct UField : UObject {
    BLCORE_MAPPED_CLASS(UField)

    BLCORE_UE3_FIELD(SuperField)
    BLCORE_UE3_FIELD(Next)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UFIELD_H
