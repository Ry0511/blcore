#include "blcore/pch.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "blcore/util/common.h"
#include "blcore/util/win_console.h"

namespace blcore {

WinConsole::WinConsole() {
    if (GetConsoleWindow() == nullptr) {
        allocated = AllocConsole() != FALSE;
    }

    HANDLE console = CreateFileW(
        L"CONOUT$",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        nullptr,
        OPEN_EXISTING,
        0,
        nullptr
    );
    handle = (console == INVALID_HANDLE_VALUE) ? nullptr : console;
}

WinConsole::~WinConsole() {
    if (handle != nullptr) {
        CloseHandle(handle);
    }

    if (allocated) {
        FreeConsole();
    }
}

void WinConsole::write(std::string_view text) const {
    if (handle == nullptr) {
        return;
    }
    const std::wstring wide = util::widen(text);
    DWORD written = 0;
    WriteConsoleW(handle, wide.data(), static_cast<DWORD>(wide.size()), &written, nullptr);
}

}  // namespace blcore
