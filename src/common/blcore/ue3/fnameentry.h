#ifndef BLCORE_UE3_FNAMEENTRY_H
#define BLCORE_UE3_FNAMEENTRY_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/layout.h"

namespace blcore::ue3 {

struct FNameEntry {
    BLCORE_MAPPED_CLASS(FNameEntry)

    BLCORE_UE3_FIELD(Index)
    BLCORE_UE3_FIELD(AnsiName)
    BLCORE_UE3_FIELD(UniName)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_FNAMEENTRY_H
