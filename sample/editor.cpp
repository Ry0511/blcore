#include "blcore/plugin/plugin_api_v1.h"
#include "blcore/util/logging.h"
#include "blcore/util/process_args.h"

#include <cstddef>
#include <string_view>

namespace {

constexpr std::string_view NAME = "sample_editor";

void BLCORE_CALL get_name(const char** out_name, std::size_t* out_size) {
    BLCORE_INFO("[{}] get_name", NAME);
    *out_name = NAME.data();
    *out_size = NAME.size();
}

void BLCORE_CALL get_version(blcore::PluginVersion_v1* out) {
    BLCORE_INFO("[{}] get_version", NAME);
    *out = {.major = 1, .minor = 0, .patch = 0};
}

blcore::ApiResult BLCORE_CALL on_load() {
    if (!blcore::util::ProcessArgs{}.is_editor()) {
        BLCORE_INFO("[{}] on_load, not the editor so unloading", NAME);
        return blcore::API_FAIL;
    }
    BLCORE_INFO("[{}] on_load", NAME);
    return blcore::API_OK;
}

void BLCORE_CALL on_shutdown() {
    BLCORE_INFO("[{}] on_shutdown", NAME);
}

}  // namespace

BLCORE_PLUGIN_ENTRY(handle) {
    BLCORE_INFO("[{}] entry", NAME);
    const blcore::PluginApi_v1 api{
        .get_name = &get_name,
        .get_version = &get_version,
        .on_load = &on_load,
        .on_shutdown = &on_shutdown,
    };
    return blcore_register_plugin_api_v1(handle, &api);
}
