#ifndef BLCORE_ENGINE_ENGINE_H
#define BLCORE_ENGINE_ENGINE_H

#include "blcore/api/gmalloc.h"
#include "blcore/api/gnames.h"
#include "blcore/api/gobjects.h"
#include "blcore/api/static_find_object.h"
#include "blcore/blcore.h"
#include "blcore/engine/gmalloc.h"
#include "blcore/engine/gnames.h"
#include "blcore/engine/gobjects.h"
#include "blcore/ue3/mapping/fwd.h"

namespace blcore::engine {

inline GObjects gobjects() {
    return GObjects{blcore_get_gobjects()};
}

inline GNames gnames() {
    return GNames{blcore_get_gnames()};
}

inline GMalloc gmalloc() {
    return GMalloc{blcore_get_gmalloc()};
}

inline ue3::UObject* static_find_object(
    ue3::UClass* cls,
    ue3::UObject* outer,
    const wchar_t* name,
    bool exact_class = false
) {
    return blcore_static_find_object(cls, outer, name, exact_class ? 1U : 0U);
}

inline void* static_find_object_address() {
    return blcore_get_static_find_object();
}

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_ENGINE_H
