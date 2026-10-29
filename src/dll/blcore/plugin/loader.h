#ifndef BLCORE_PLUGIN_LOADER_H
#define BLCORE_PLUGIN_LOADER_H

#include "blcore/blcore.h"
#include "blcore/plugin/plugin_api_v1.h"
#include "blcore/util/logging.h"

#include <exception>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

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

template <typename Fn>
bool invoke_guarded(std::string_view what, Fn&& fn) {
    try {
        std::forward<Fn>(fn)();
        return true;
    } catch (const std::exception& ex) {
        BLCORE_ERROR("{} threw: {}", what, ex.what());
    } catch (...) {
        BLCORE_ERROR("{} threw an unknown exception", what);
    }
    return false;
}

}  // namespace blcore

#endif  // BLCORE_PLUGIN_LOADER_H
