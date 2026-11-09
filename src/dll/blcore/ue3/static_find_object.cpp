#include "blcore/pch.h"

#include "blcore/api/static_find_object.h"
#include "blcore/game/game.h"
#include "blcore/util/logging.h"

BLCORE_API_FN(
    blcore::ue3::UObject*,
    blcore_static_find_object,
    blcore::ue3::UClass* cls,
    blcore::ue3::UObject* outer,
    const wchar_t* name,
    uint32_t exact_class
) {
    const auto static_find_object = blcore::game::current().static_find_object();
    if (static_find_object == nullptr) {
        BLCORE_ERROR("failed to find StaticFindObject");
        return nullptr;
    }
    return static_find_object(cls, outer, name, exact_class);
}

BLCORE_API_FN(void*, blcore_get_static_find_object) {
    return reinterpret_cast<void*>(blcore::game::current().static_find_object());
}
