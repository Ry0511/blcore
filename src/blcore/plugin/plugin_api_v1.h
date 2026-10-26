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

using PluginApi_OnLoad = void(__cdecl*)();
using PluginApi_OnShutdown = void(__cdecl*)();
using PluginApi_GetName = void(__cdecl*)(const char** out_name, std::size_t* out_size);
using PluginApi_GetVersion = void(__cdecl*)(PluginVersion_v1* out);

struct PluginApi_v1 {
    PluginApi_GetName get_name;        // the name of this plugin
    PluginApi_GetVersion get_version;  // the version of this plugin
    PluginApi_OnLoad on_load;          // called once the .exe has been unpacked
    PluginApi_OnShutdown on_shutdown;  // called before blcore shuts down
};

}  // namespace blcore

BLCORE_API_FN(bool, blcore_register_plugin_api_v1, blcore::PluginHandle* handle, const blcore::PluginApi_v1* api);

// NOLINTBEGIN(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)
#define BLCORE_PLUGIN_ENTRY(handle) \
    extern "C" __declspec(dllexport) bool __cdecl blcore_plugin_entry(::blcore::PluginHandle* handle) noexcept(false)
// NOLINTEND(cppcoreguidelines-macro-usage, bugprone-macro-parentheses)

#endif  // BLCORE_PLUGIN_API_V1_H
