#ifndef BLCORE_PLUGIN_PLUGIN_RUNTIME_H
#define BLCORE_PLUGIN_PLUGIN_RUNTIME_H

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
    fs::path path;
    void* module = nullptr;
    std::string name;
    std::optional<PluginApi_v1> plugin_api_v1;
    bool started = false;
    bool unload_requested = false;
};

class PluginRuntime {
   public:
    void load(const fs::path& dir);
    void shutdown();

   private:
    std::vector<std::unique_ptr<PluginHandle>> m_Plugins;
};

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

#endif  // BLCORE_PLUGIN_PLUGIN_RUNTIME_H
