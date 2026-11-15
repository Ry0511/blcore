#include "blcore/pch.h"

#include "blcore/api/static_load_object.h"
#include "blcore/game/game.h"
#include "blcore/util/logging.h"

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
) {
    const auto static_load_object = blcore::game::current().static_load_object();
    if (static_load_object == nullptr) {
        BLCORE_ERROR("failed to find StaticLoadObject");
        return nullptr;
    }
    return static_load_object(cls, outer, name, filename, load_flags, sandbox, allow_object_reconciliation);
}

BLCORE_API_FN(void*, blcore_get_static_load_object) {
    return reinterpret_cast<void*>(blcore::game::current().static_load_object());
}
