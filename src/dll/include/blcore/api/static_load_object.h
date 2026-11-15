#ifndef BLCORE_API_STATIC_LOAD_OBJECT_H
#define BLCORE_API_STATIC_LOAD_OBJECT_H

#include "blcore/api/api.h"
#include "blcore/blcore.h"
#include "blcore/ue3/mapping/fwd.h"

BLCORE_API_FN(
    blcore::ue3::UObject*,
    blcore_static_load_object,
    blcore::ue3::UClass* cls,
    blcore::ue3::UObject* outer,
    const wchar_t* name,
    const wchar_t* filename,
    uint32_t load_flags,
    blcore::ue3::UObject* sandbox,
    uint32_t allow_object_reconciliation
);

BLCORE_API_FN(void*, blcore_get_static_load_object);

#endif  // BLCORE_API_STATIC_LOAD_OBJECT_H
