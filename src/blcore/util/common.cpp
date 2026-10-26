#include "blcore/pch.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

#include "blcore/util/common.h"

namespace blcore::util {

fs::path module_dir(void* module) {
    std::array<wchar_t, MAX_PATH> path{};
    const DWORD len = GetModuleFileNameW(
        static_cast<HMODULE>(module),
        path.data(),
        static_cast<DWORD>(path.size())
    );

    if (len == 0 || len == path.size()) {
        return {};
    }

    return fs::path{
        std::wstring_view{path.data(), len}
    }.parent_path();
}

// NOLINTBEGIN(bugprone-suspicious-stringview-data-usage)
std::string narrow(std::wstring_view str) {
    if (str.empty()) {
        return {};
    }
    const auto str_len = static_cast<int>(str.size());
    const int size = WideCharToMultiByte(CP_UTF8, 0, str.data(), str_len, nullptr, 0, nullptr, nullptr);
    std::string out(static_cast<size_t>(size), '\0');
    WideCharToMultiByte(CP_UTF8, 0, str.data(), str_len, out.data(), size, nullptr, nullptr);
    return out;
}

std::wstring widen(std::string_view str) {
    if (str.empty()) {
        return {};
    }
    const auto str_len = static_cast<int>(str.size());
    const int size = MultiByteToWideChar(CP_UTF8, 0, str.data(), str_len, nullptr, 0);
    std::wstring out(static_cast<size_t>(size), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, str.data(), str_len, out.data(), size);
    return out;
}
// NOLINTEND(bugprone-suspicious-stringview-data-usage)

}  // namespace blcore::util
