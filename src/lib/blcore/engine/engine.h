#ifndef BLCORE_ENGINE_ENGINE_H
#define BLCORE_ENGINE_ENGINE_H

#include "blcore/blcore.h"
#include "blcore/engine/gmalloc.h"
#include "blcore/engine/gnames.h"
#include "blcore/engine/gobjects.h"
#include "blcore/engine/object.h"
#include "blcore/plugin/engine_api_v1.h"
#include "blcore/plugin/globals_api_v1.h"
#include "blcore/plugin/plugin.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/uobject/uclass.h"

namespace blcore::engine {

inline GObjects gobjects() {
    const auto gobjects = globals_api().gobjects;
    return GObjects{gobjects != nullptr ? gobjects() : nullptr};
}

inline GNames gnames() {
    const auto gnames = globals_api().gnames;
    return GNames{gnames != nullptr ? gnames() : nullptr};
}

inline GMalloc gmalloc() {
    const auto gmalloc = globals_api().gmalloc;
    return GMalloc{gmalloc != nullptr ? gmalloc() : nullptr};
}

inline ue3::UObject* static_find_object(
    ue3::UClass* cls,
    ue3::UObject* outer,
    const wchar_t* name,
    bool exact_class = false
) {
    const auto static_find_object = engine_api().static_find_object;
    if (static_find_object == nullptr) {
        return nullptr;
    }
    return static_find_object(cls, outer, name, exact_class ? 1U : 0U);
}

inline void* static_find_object_address() {
    return engine_api().static_find_object_address;
}

inline ue3::UObject* static_load_object(
    ue3::UClass* cls,
    ue3::UObject* outer,
    const wchar_t* name,
    const wchar_t* filename = nullptr,
    uint32_t load_flags = 0,
    ue3::UObject* sandbox = nullptr,
    bool allow_object_reconciliation = true
) {
    const auto static_load_object = engine_api().static_load_object;
    if (static_load_object == nullptr) {
        return nullptr;
    }
    return static_load_object(
        cls,
        outer,
        name,
        filename,
        load_flags,
        sandbox,
        allow_object_reconciliation ? 1U : 0U
    );
}

inline void* static_load_object_address() {
    return engine_api().static_load_object_address;
}

inline ue3::UObject* find_object(const wchar_t* path) {
    return static_find_object(nullptr, nullptr, path);
}

template <typename T = ue3::UObject>
T* find_object(ue3::UClass* cls, const wchar_t* path) {
    return static_cast<T*>(static_find_object(cls, nullptr, path));
}

template <typename T = ue3::UObject>
T* load_object(ue3::UClass* cls, const wchar_t* path, uint32_t load_flags = 0) {
    return static_cast<T*>(static_load_object(cls, nullptr, path, nullptr, load_flags));
}

inline ue3::UClass* find_class(const wchar_t* path) {
    static ue3::UClass* class_class = nullptr;
    if (class_class == nullptr) {
        class_class = find_object<ue3::UClass>(nullptr, L"Core.Class");
    }

    return (class_class != nullptr)
               ? find_object<ue3::UClass>(class_class, path)
               : nullptr;
}

}  // namespace blcore::engine

#endif  // BLCORE_ENGINE_ENGINE_H
