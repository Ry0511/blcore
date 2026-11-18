#include "blcore/pch.h"

#include "blcore/game/game.h"
#include "blcore/plugin/globals_api_v1.h"
#include "blcore/util/logging.h"

namespace blcore {

namespace {

ue3::TArray<ue3::UObject*>* BLCORE_CALL gobjects() noexcept(false) {
    return static_cast<ue3::TArray<ue3::UObject*>*>(game::current().address_table().gobjects);
}

ue3::TArray<ue3::FNameEntry*>* BLCORE_CALL gnames() noexcept(false) {
    return static_cast<ue3::TArray<ue3::FNameEntry*>*>(game::current().address_table().gnames);
}

ue3::FMalloc** BLCORE_CALL gmalloc() noexcept(false) {
    return static_cast<ue3::FMalloc**>(game::current().address_table().gmalloc);
}

}  // namespace

}  // namespace blcore

BLCORE_API_FN(
    blcore::ApiResult,
    blcore_get_globals_api_v1,
    blcore::PluginHandle* handle,
    blcore::GlobalsApi_v1* out
) {
    if (handle == nullptr || out == nullptr) {
        BLCORE_ERROR("get GlobalsApi_v1 called with null parameter");
        return blcore::API_FAIL;
    }

    *out = blcore::GlobalsApi_v1{
        .gobjects = &blcore::gobjects,
        .gnames = &blcore::gnames,
        .gmalloc = &blcore::gmalloc,
    };
    return blcore::API_OK;
}
