#ifndef BLCORE_UE3_UFUNCTION_H
#define BLCORE_UE3_UFUNCTION_H

#include "blcore/ue3/impl/bl1_core.h"
#include "blcore/ue3/impl/bl1e_core.h"
#include "blcore/ue3/field.h"
#include "blcore/ue3/fname.h"
#include "blcore/ue3/fwd.h"
#include "blcore/ue3/layout.h"
#include "blcore/ue3/ustruct.h"

namespace blcore::ue3 {

struct UFunction : UStruct {
    BLCORE_MAPPED_CLASS(UFunction)

    BLCORE_UE3_FIELD(FunctionFlags)
    BLCORE_UE3_FIELD(iNative)
    BLCORE_UE3_FIELD(RepOffset)
    BLCORE_UE3_FIELD(FriendlyName)
    BLCORE_UE3_FIELD(OperPrecedence)
    BLCORE_UE3_FIELD(NumParms)
    BLCORE_UE3_FIELD(ParmsSize)
    BLCORE_UE3_FIELD(ReturnValueOffset)
    BLCORE_UE3_FIELD(FirstStructWithDefaults)
    BLCORE_UE3_FIELD(Func)
};

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UFUNCTION_H
