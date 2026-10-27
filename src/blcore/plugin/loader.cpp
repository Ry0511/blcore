#include "blcore/pch.h"

#include "blcore/plugin/loader.h"
#include "blcore/util/common.h"
#include "blcore/util/logging.h"

namespace blcore {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

constexpr auto ENTRY_NAME = "blcore_plugin_entry";
using EntryFn = ApiResult(BLCORE_CALL*)(PluginHandle* handle) noexcept(false);

std::vector<std::unique_ptr<PluginHandle>> plugins;

std::string plugin_name(const PluginApi_v1& api, const fs::path& path) {
    const char* name = nullptr;
    size_t size = 0;
    api.get_name(&name, &size);
    return (name != nullptr)
               ? std::string{name, size}
               : util::narrow(path.stem().wstring());
}

std::string plugin_version(const PluginApi_v1& api) {
    PluginVersion_v1 version{};
    api.get_version(&version);
    return std::format("{}.{}.{}", version.major, version.minor, version.patch);
}

std::unique_ptr<PluginHandle> load_plugin(const fs::path& path) {
    const std::string file = util::narrow(path.filename().wstring());

    void* module = util::load_library(path);
    if (module == nullptr) {
        BLCORE_ERROR("Failed to load {}", file);
        return nullptr;
    }

    // grab the entry function if it exists, if not, log and skip
    auto entry = reinterpret_cast<EntryFn>(util::get_proc_address(module, ENTRY_NAME));
    if (entry == nullptr) {
        BLCORE_WARN("{} doesn't export {}, skipping it", file, ENTRY_NAME);
        util::free_library(module);
        return nullptr;
    }

    auto handle = std::make_unique<PluginHandle>();
    handle->path = path;
    handle->module = module;

    const auto unload = [module]() -> std::unique_ptr<PluginHandle> {
        util::free_library(module);
        return nullptr;
    };

    ApiResult result{API_FAIL};
    bool success = util::invoke_guarded(
        file,
        [&result, &entry, &handle] {
            result = entry(handle.get());
        }
    );

    if (!success || result != API_OK || !handle->plugin_api_v1.has_value()) {
        BLCORE_INFO("{} failed to load", file);
        return unload();
    }

    // grab the plugin name and version from the api
    const PluginApi_v1& api = *handle->plugin_api_v1;
    std::string version{};
    success = util::invoke_guarded(file, [&handle, &api, &path, &version] {
        handle->name = plugin_name(api, path);
        version = plugin_version(api);
    });

    if (!success) {
        return unload();
    }

    BLCORE_INFO("Loaded plugin {} v{}", handle->name, version);
    return handle;
}

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

void load_plugins(const fs::path& dir) {
    std::error_code error{};
    if (!fs::is_directory(dir, error)) {
        BLCORE_INFO("No plugin folder at {}", util::narrow(dir.wstring()));

        if (!fs::create_directories(dir, error) && error) {
            BLCORE_ERROR("Failed to create plugin folder at {}: {}", util::narrow(dir.wstring()), error.message());
        }
        return;
    }

    std::vector<fs::path> paths{};
    for (const auto& entry : fs::directory_iterator{dir, error}) {
        if (entry.is_regular_file(error) && entry.path().extension() == ".dll") {
            paths.push_back(entry.path());
        }
    }
    std::ranges::sort(paths);

    // load and store all valid plugins
    for (const auto& path : paths) {
        if (auto handle = load_plugin(path)) {
            plugins.push_back(std::move(handle));
        }
    }

    // invoke on_load on all plugins
    for (const auto& handle : plugins) {
        if (handle->plugin_api_v1) {
            BLCORE_INFO("loading plugin {}", handle->name);
            ApiResult result{API_FAIL};
            const bool success = util::invoke_guarded(handle->name, [&result, &handle] {
                result = handle->plugin_api_v1->on_load();
            });
            // not all plugins will want to stay loaded such as editor only, make only, game only
            //  plugins only run in certain contexts.
            handle->unload_requested = !success || result != API_OK;
        }
    }

    // unload any plugins that requested to be unloaded or raised an exception in on_load
    for (const auto& handle : plugins) {
        if (handle->unload_requested && handle->plugin_api_v1) {
            BLCORE_INFO("unloading plugin {}", handle->name);
            util::invoke_guarded(handle->name, handle->plugin_api_v1->on_shutdown);
            util::free_library(handle->module);
        }
    }
    std::erase_if(plugins, [](const auto& handle) { return handle->unload_requested; });
}

void shutdown_plugins() {
    for (const auto& handle : std::views::reverse(plugins)) {
        if (handle->plugin_api_v1) {
            util::invoke_guarded(handle->name, handle->plugin_api_v1->on_shutdown);
        }
    }
}
}  // namespace blcore
