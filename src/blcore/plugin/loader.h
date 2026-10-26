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
    std::string name;                           // plugin name from api
    std::optional<PluginApi_v1> plugin_api_v1;  // entry point api
};

void load_plugins(const fs::path& dir);

}  // namespace blcore

#endif  // BLCORE_EXPORTS

#endif  // BLCORE_PLUGIN_LOADER_H
