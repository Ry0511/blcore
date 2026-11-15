#include "blcore/plugin/plugin.h"
#include "blcore/plugin/engine_api_v1.h"
#include "blcore/plugin/globals_api_v1.h"
#include "blcore/plugin/plugin_api_v1.h"

namespace blcore {

namespace {

EngineApi_v1 _engine_api{};
GlobalsApi_v1 _globals_api{};

}  // namespace

ApiResult register_api(PluginHandle* handle, const PluginApi_v1& api) {
    const ApiResult result = blcore_register_plugin_api_v1(handle, &api);
    if (result != API_OK) {
        return result;
    }
    const ApiResult engine_result = blcore_get_engine_api_v1(handle, &_engine_api);
    if (engine_result != API_OK) {
        return engine_result;
    }
    return blcore_get_globals_api_v1(handle, &_globals_api);
}

const EngineApi_v1& engine_api() {
    return _engine_api;
}

const GlobalsApi_v1& globals_api() {
    return _globals_api;
}

}  // namespace blcore
