#include "blcore/pch.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include <MinHook.h>
#include <libhat.hpp>

#include "blcore/plugin/loader.h"
#include "blcore/util/common.h"
#include "blcore/util/logging.h"
#include "blcore/version.h"

namespace blcore {

////////////////////////////////////////////////////////////////////////////////
// | STARTUP |
////////////////////////////////////////////////////////////////////////////////

namespace {

DWORD WINAPI startup_thread(LPVOID h_module) {
    logging::set_console_logging(true);
    logging::add_log_file(util::module_dir(h_module) / "blcore.log");
    logging::initialise();
    logging::log(logging::Level::Info, get_version_string());
    return 0;
}

void detach() {
    logging::terminate();
}

////////////////////////////////////////////////////////////////////////////////
// | PLUGINS |
////////////////////////////////////////////////////////////////////////////////

using IsDebuggerPresentFn = BOOL(WINAPI*)();

HMODULE blcore_module = nullptr;
IsDebuggerPresentFn original_is_debugger_present = nullptr;
std::atomic_bool plugins_loaded{false};
std::mutex api_mutex;

// pretty much a carbon copy of the unrealsdk here
bool is_unpacked() {
#ifdef WILLOW64
    static constexpr auto ENTRY_SIG = hat::compile_signature<
        "48 8B D8 48 83 38 00 74 ?? 48 8B C8 E8 ?? ?? ?? ?? 84 C0">();
#elifdef WILLOW
    static constexpr auto ENTRY_SIG = hat::compile_signature<
        "6A 58 68 ?? ?? ?? ?? E8 ?? ?? ?? ?? 33 DB">();
#endif
    return hat::find_pattern(ENTRY_SIG, ".text").has_result();
}

BOOL WINAPI is_debugger_present_hook() {
    if (plugins_loaded) {
        return original_is_debugger_present();
    }

    // the game may call this from several threads at once, only the first one loads plugins.
    const std::scoped_lock lock{api_mutex};
    if (!plugins_loaded && is_unpacked()) {
        plugins_loaded = true;
        try {
            // we only start loading plugins once the game has been unpacked, we also do it here
            // while we have the game blocked so that any on_load plugin code can run immediately.
            load_plugins(util::module_dir(blcore_module) / "blcore");
        } catch (const std::exception& ex) {
            BLCORE_ERROR("Loading plugins failed: {}", ex.what());
        }
    }

    return original_is_debugger_present();
}

////////////////////////////////////////////////////////////////////////////////
// | SHUTDOWN |
////////////////////////////////////////////////////////////////////////////////

using ExitProcessFn = void(WINAPI*)(UINT exit_code);

ExitProcessFn original_exit_process = nullptr;
std::atomic_bool shutting_down{false};

void WINAPI exit_process_hook(UINT exit_code) {
    if (!shutting_down.exchange(true)) {
        BLCORE_INFO("Shutting down");
        {
            const std::scoped_lock lock{api_mutex};
            shutdown_plugins();
        }
        // we do this in detach as well, its better to do it here but both places don't hurt
        logging::terminate(true);
    }

    original_exit_process(exit_code);
}

////////////////////////////////////////////////////////////////////////////////
// | HOOKS |
////////////////////////////////////////////////////////////////////////////////

MH_STATUS hook_kernel32(const char* name, void* detour, void** original) {
    void* target = nullptr;
    MH_STATUS status = MH_CreateHookApiEx(L"kernel32", name, detour, original, &target);
    if (status == MH_OK) {
        status = MH_EnableHook(target);
    }
    return status;
}

void install_hooks(HMODULE h_module) {
    blcore_module = h_module;

    const MH_STATUS init = MH_Initialize();
    if (init != MH_OK && init != MH_ERROR_ALREADY_INITIALIZED) {
        BLCORE_ERROR(
            "MinHook failed to initialise, plugins won't load: {}",
            MH_StatusToString(init)
        );
        return;
    }

    // called before the game initialises but after the executable has been decrypted
    MH_STATUS status = hook_kernel32(
        "IsDebuggerPresent",
        reinterpret_cast<void*>(&is_debugger_present_hook),
        reinterpret_cast<void**>(&original_is_debugger_present)
    );
    if (status != MH_OK) {
        BLCORE_ERROR(
            "Failed to hook IsDebuggerPresent, plugins won't load: {}",
            MH_StatusToString(status)
        );
    }

    // little better than using detach which is much later and doesn't guarantee shutdown order.
    // this happens while all modules are still loaded so we can notify them to shutdown before we
    // shutdown.
    status = hook_kernel32(
        "ExitProcess",
        reinterpret_cast<void*>(&exit_process_hook),
        reinterpret_cast<void**>(&original_exit_process)
    );
    if (status != MH_OK) {
        BLCORE_ERROR(
            "Failed to hook ExitProcess, plugins won't be shut down: {}",
            MH_StatusToString(status)
        );
    }
}

}  // namespace

}  // namespace blcore

////////////////////////////////////////////////////////////////////////////////
// | WINDOWS SHIT |
////////////////////////////////////////////////////////////////////////////////

// NOLINTNEXTLINE(misc-use-internal-linkage)
BOOL APIENTRY DllMain(HMODULE h_module, DWORD reason, LPVOID /*reserved*/) {
    switch (reason) {
        case DLL_PROCESS_ATTACH: {
            DisableThreadLibraryCalls(h_module);
            blcore::install_hooks(h_module);
            CreateThread(nullptr, 0, &blcore::startup_thread, h_module, 0, nullptr);
            break;
        }

        case DLL_PROCESS_DETACH: {
            blcore::detach();
            break;
        }

        default: {
            break;
        }
    }
    return TRUE;
}
