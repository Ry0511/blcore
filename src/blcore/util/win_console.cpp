#include "blcore/pch.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "blcore/util/common.h"
#include "blcore/util/win_console.h"

namespace blcore {

WinConsole::WinConsole() {
    if (GetConsoleWindow() == nullptr) {
        m_Allocated = AllocConsole() != FALSE;
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
    m_Handle = (console == INVALID_HANDLE_VALUE) ? nullptr : console;
}

WinConsole::~WinConsole() {
    if (m_Handle != nullptr) {
        CloseHandle(m_Handle);
    }

    if (m_Allocated) {
        FreeConsole();
    }
}

void WinConsole::write(std::string_view text) const {
    if (m_Handle == nullptr) {
        return;
    }
    const std::wstring wide = util::widen(text);
    DWORD written = 0;
    WriteConsoleW(m_Handle, wide.data(), static_cast<DWORD>(wide.size()), &written, nullptr);
}

}  // namespace blcore
