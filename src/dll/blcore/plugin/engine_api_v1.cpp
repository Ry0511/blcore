#include "blcore/pch.h"

#include "blcore/game/game.h"
#include "blcore/plugin/engine_api_v1.h"
#include "blcore/util/logging.h"

namespace blcore {

namespace {

using StaticFindObjectFn = ue3::UObject*(__cdecl*)(ue3::UClass*, ue3::UObject*, const wchar_t*, uint32_t);

using StaticLoadObjectFn = ue3::UObject*(__cdecl*)(ue3::UClass*,
                                                   ue3::UObject*,
                                                   const wchar_t*,
                                                   const wchar_t*,
                                                   uint32_t,
                                                   ue3::UObject*,
                                                   uint32_t);

ue3::UObject* BLCORE_CALL static_find_object(
    ue3::UClass* cls,
    ue3::UObject* outer,
    const wchar_t* name,
    uint32_t exact_class
) noexcept(false) {
    void* address = game::current().address_table().static_find_object;
    if (address == nullptr) {
        BLCORE_ERROR("failed to find StaticFindObject");
        return nullptr;
    }
    return reinterpret_cast<StaticFindObjectFn>(address)(cls, outer, name, exact_class);
}

ue3::UObject* BLCORE_CALL static_load_object(
    ue3::UClass* cls,
    ue3::UObject* outer,
    const wchar_t* name,
    const wchar_t* filename,
    uint32_t load_flags,
    ue3::UObject* sandbox,
    uint32_t allow_object_reconciliation
) noexcept(false) {
    void* address = game::current().address_table().static_load_object;
    if (address == nullptr) {
        BLCORE_ERROR("failed to find StaticLoadObject");
        return nullptr;
    }
    return reinterpret_cast<StaticLoadObjectFn>(address)(
        cls,
        outer,
        name,
        filename,
        load_flags,
        sandbox,
        allow_object_reconciliation
    );
}

}  // namespace

}  // namespace blcore

BLCORE_API_FN(
    blcore::ApiResult,
    blcore_get_engine_api_v1,
    blcore::PluginHandle* handle,
    blcore::EngineApi_v1* out
) {
    if (handle == nullptr || out == nullptr) {
        BLCORE_ERROR("get EngineApi_v1 called with null parameter");
        return blcore::API_FAIL;
    }

    const blcore::game::AddressTable& table = blcore::game::current().address_table();
    *out = blcore::EngineApi_v1{
        .static_find_object = &blcore::static_find_object,
        .static_find_object_address = table.static_find_object,
        .static_load_object = &blcore::static_load_object,
        .static_load_object_address = table.static_load_object,
    };
    return blcore::API_OK;
}
