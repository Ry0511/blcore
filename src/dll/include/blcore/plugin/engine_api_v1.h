#ifndef BLCORE_PLUGIN_ENGINE_API_V1_H
#define BLCORE_PLUGIN_ENGINE_API_V1_H

#include "blcore/api/api.h"
#include "blcore/blcore.h"
#include "blcore/ue3/mapping/fwd.h"

namespace blcore {

struct PluginHandle;

// clang-format off

using EngineApi_StaticFindObject = ue3::UObject*(BLCORE_CALL*)(
    ue3::UClass * cls,
    ue3::UObject* outer,
    const wchar_t* name,
    uint32_t exact_class
) noexcept(false);

using EngineApi_StaticLoadObject = ue3::UObject*(BLCORE_CALL*)(
    ue3::UClass * cls,
    ue3::UObject* outer,
    const wchar_t* name,
    const wchar_t* filename,
    uint32_t load_flags,
    ue3::UObject* sandbox,
    uint32_t allow_object_reconciliation
) noexcept(false);

// clang-format on

struct EngineApi_v1 {
    EngineApi_StaticFindObject static_find_object{nullptr};
    void* static_find_object_address{nullptr};
    EngineApi_StaticLoadObject static_load_object{nullptr};
    void* static_load_object_address{nullptr};
};

}  // namespace blcore

BLCORE_API_FN(
    blcore::ApiResult,
    blcore_get_engine_api_v1,
    blcore::PluginHandle* handle,
    blcore::EngineApi_v1* out
);

#endif  // BLCORE_PLUGIN_ENGINE_API_V1_H
