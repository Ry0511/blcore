#ifndef BLCORE_UE3_UENUM_H
#define BLCORE_UE3_UENUM_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/layout.h"
#include "blcore/ue3/tarray.h"
#include "blcore/ue3/ufield.h"

namespace blcore::ue3 {

struct UEnum : UField {
    BLCORE_MAPPED_CLASS(UEnum)

    BLCORE_UE3_FIELD(Names)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UENUM_H
