#include "blcore/plugin/plugin.h"
#include "blcore/plugin/plugin_api_v1.h"

namespace blcore {

ApiResult register_api(PluginHandle* handle, const PluginApi_v1& api) {
    return blcore_register_plugin_api_v1(handle, &api);
}

}  // namespace blcore
