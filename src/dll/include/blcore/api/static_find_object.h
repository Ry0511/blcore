#ifndef BLCORE_API_STATIC_FIND_OBJECT_H
#define BLCORE_API_STATIC_FIND_OBJECT_H

#include "blcore/api/api.h"
#include "blcore/blcore.h"
#include "blcore/ue3/mapping/fwd.h"

BLCORE_API_FN(
    blcore::ue3::UObject*,
    blcore_static_find_object,
    blcore::ue3::UClass* cls,
    blcore::ue3::UObject* outer,
    const wchar_t* name,
    uint32_t exact_class
);

BLCORE_API_FN(void*, blcore_get_static_find_object);

#endif  // BLCORE_API_STATIC_FIND_OBJECT_H
