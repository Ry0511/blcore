#ifndef BLCORE_ENGINE_OBJECT_H
#define BLCORE_ENGINE_OBJECT_H

#include "blcore/blcore.h"
#include "blcore/ue3/uobject/uclass.h"
#include "blcore/ue3/uobject/uobject.h"
#include "blcore/ue3/uobject/ustruct.h"

namespace blcore::engine {

inline auto* const ANY_PACKAGE = reinterpret_cast<ue3::UObject*>(~uintptr_t{0});

inline bool is_instance(const ue3::UObject* obj, const ue3::UClass* cls) {
    if (obj == nullptr || cls == nullptr) {
        return false;
    }

    for (const ue3::UStruct* it = obj->Class(); it != nullptr; it = it->SuperField()) {
        if (it == cls) {
            return true;
        }
    }
    return false;
}

inline bool is_parent(const ue3::UObject* obj, const ue3::UObject* outer) {
    if (obj == nullptr || outer == nullptr) {
        return false;
    }

    for (const ue3::UObject* it = obj->Outer(); it != nullptr; it = it->Outer()) {
        if (it == outer) {
            return true;
        }
    }
    return false;
}

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_OBJECT_H
