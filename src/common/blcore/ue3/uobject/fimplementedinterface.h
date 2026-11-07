#ifndef BLCORE_UE3_UOBJECT_FIMPLEMENTEDINTERFACE_H
#define BLCORE_UE3_UOBJECT_FIMPLEMENTEDINTERFACE_H

#include "blcore/ue3/mapping/fwd.h"

namespace blcore::ue3 {

#pragma pack(push, 4)

struct FImplementedInterface {
    UClass* Class{nullptr};
    UProperty* PointerProperty{nullptr};
};

#pragma pack(pop)

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_UOBJECT_FIMPLEMENTEDINTERFACE_H
