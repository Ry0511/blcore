#ifndef BLCORE_PLUGIN_LOADER_H
#define BLCORE_PLUGIN_LOADER_H

#ifdef BLCORE_EXPORTS

#include "blcore/blcore.h"
#include "blcore/plugin/plugin_api_v1.h"

#include <optional>
#include <string>

namespace blcore {

struct PluginHandle {
    fs::path path;                              // absolute path to .dll
    void* module = nullptr;                     // hmodule
    std::string name;                           // plugin name from api (or dll name)
    std::optional<PluginApi_v1> plugin_api_v1;  // entry point api
    bool unload_requested = false;              // plugin will be unloaded soon
};

void load_plugins(const fs::path& dir);
void shutdown_plugins();

}  // namespace blcore

#endif  // BLCORE_EXPORTS

#endif  // BLCORE_PLUGIN_LOADER_H
