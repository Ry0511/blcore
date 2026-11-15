#ifndef BLCORE_PLUGIN_PLUGIN_H
#define BLCORE_PLUGIN_PLUGIN_H

#include "blcore/api/api.h"

namespace blcore {

struct PluginHandle;
struct PluginApi_v1;
struct EngineApi_v1;

ApiResult register_api(PluginHandle* handle, const PluginApi_v1& api);

const EngineApi_v1& engine_api();

}  // namespace blcore

#endif  // BLCORE_PLUGIN_PLUGIN_H
