#ifndef BLCORE_PLUGIN_GLOBALS_API_V1_H
#define BLCORE_PLUGIN_GLOBALS_API_V1_H

#include "blcore/api/api.h"
#include "blcore/blcore.h"
#include "blcore/ue3/mapping/fwd.h"
#include "blcore/ue3/tarray.h"

namespace blcore {

struct PluginHandle;

using GlobalsApi_GObjects = ue3::TArray<ue3::UObject*>*(BLCORE_CALL*)() noexcept(false);
using GlobalsApi_GNames = ue3::TArray<ue3::FNameEntry*>*(BLCORE_CALL*)() noexcept(false);
using GlobalsApi_GMalloc = ue3::FMalloc**(BLCORE_CALL*)() noexcept(false);

struct GlobalsApi_v1 {
    GlobalsApi_GObjects gobjects{nullptr};
    GlobalsApi_GNames gnames{nullptr};
    GlobalsApi_GMalloc gmalloc{nullptr};
};

}  // namespace blcore

BLCORE_API_FN(
    blcore::ApiResult,
    blcore_get_globals_api_v1,
    blcore::PluginHandle* handle,
    blcore::GlobalsApi_v1* out
);

#endif  // BLCORE_PLUGIN_GLOBALS_API_V1_H
