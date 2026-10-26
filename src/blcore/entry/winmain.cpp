#include "blcore/pch.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "blcore/util/common.h"
#include "blcore/util/logging.h"
#include "blcore/version.h"

namespace blcore {

////////////////////////////////////////////////////////////////////////////////
// | STARTUP |
////////////////////////////////////////////////////////////////////////////////

namespace {

DWORD WINAPI startup_thread(LPVOID h_module) {
    logging::initialise();
    logging::set_console_logging(true);
    logging::add_log_file(util::module_dir(h_module) / "blcore.log");
    logging::log(logging::Level::Info, get_version_string());
    return 0;
}

void detach() {
    logging::terminate();
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
