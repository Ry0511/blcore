#ifndef BLCORE_PLUGIN_API_V1_H
#define BLCORE_PLUGIN_API_V1_H

#include "blcore/api/api.h"

#include <cstddef>

namespace blcore {

struct PluginHandle;

struct PluginVersion_v1 {
    int major;
    int minor;
    int patch;
};

using PluginApi_OnLoad = void(BLCORE_CALL*)() noexcept(false);
using PluginApi_OnShutdown = void(BLCORE_CALL*)() noexcept(false);
using PluginApi_GetName = void(BLCORE_CALL*)(const char** out_name, std::size_t* out_size) noexcept(false);
using PluginApi_GetVersion = void(BLCORE_CALL*)(PluginVersion_v1* out) noexcept(false);

struct PluginApi_v1 {
    PluginApi_GetName get_name{nullptr};        // the name of this plugin
    PluginApi_GetVersion get_version{nullptr};  // the version of this plugin
    PluginApi_OnLoad on_load{nullptr};          // called once the .exe has been unpacked
    PluginApi_OnShutdown on_shutdown{nullptr};  // called before blcore shuts down
};

}  // namespace blcore

BLCORE_API_FN(bool, blcore_register_plugin_api_v1, blcore::PluginHandle* handle, const blcore::PluginApi_v1* api);

// NOLINTBEGIN(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)
#define BLCORE_PLUGIN_ENTRY(handle) \
    extern "C" BLCORE_EXPORT bool BLCORE_CALL blcore_plugin_entry(::blcore::PluginHandle* handle) noexcept(false)
// NOLINTEND(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)

#endif  // BLCORE_PLUGIN_API_V1_H
