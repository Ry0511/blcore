#ifndef BLCORE_UE3_FMALLOC_H
#define BLCORE_UE3_FMALLOC_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/mapping/field.h"
#include "blcore/ue3/mapping/layout.h"
#include "blcore/ue3/mapping/vfunc.h"

namespace blcore::ue3 {

struct FMalloc {
    BLCORE_MAPPED_CLASS(FMalloc)

    BLCORE_UE3_VFUNC(Malloc)
    BLCORE_UE3_VFUNC(Realloc)
    BLCORE_UE3_VFUNC(Free)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_FMALLOC_H
