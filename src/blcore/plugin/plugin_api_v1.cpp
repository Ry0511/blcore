#include "blcore/pch.h"

#include "blcore/plugin/loader.h"
#include "blcore/plugin/plugin_api_v1.h"
#include "blcore/util/common.h"
#include "blcore/util/logging.h"

BLCORE_API_FN(
    bool,
    blcore_register_plugin_api_v1,
    blcore::PluginHandle* handle,
    const blcore::PluginApi_v1* api
) {
    if (handle == nullptr || api == nullptr) {
        BLCORE_ERROR("register PluginApi_v1 called with null parameter");
        return false;
    }

    const std::string file = blcore::util::narrow(handle->path.filename().wstring());
    if (handle->plugin_api_v1.has_value()) {
        BLCORE_WARN("PluginApi_v1 already registered for {}", file);
        return false;
    }

    if (
        api->on_load == nullptr
        || api->on_shutdown == nullptr
        || api->get_name == nullptr
        || api->get_version == nullptr
    ) {
        BLCORE_ERROR("failed to load {} as it did not register all of PluginApi_v1", file);
        return false;
    }

    handle->plugin_api_v1 = *api;
    return true;
}
