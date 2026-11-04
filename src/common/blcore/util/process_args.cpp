#include <algorithm>
#include <span>
#include <string>
#include <string_view>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <shellapi.h>

#include "blcore/blcore.h"
#include "blcore/util/common.h"
#include "blcore/util/process_args.h"

namespace blcore::util {

namespace {

bool equals_icase(std::wstring_view lhs, std::wstring_view rhs) {
    return CompareStringOrdinal(
               lhs.data(),
               static_cast<int>(lhs.size()),
               rhs.data(),
               static_cast<int>(rhs.size()),
               TRUE
           )
           == CSTR_EQUAL;
}

std::span<wchar_t*> user_args(wchar_t** argv, size_t argc) {
    if (argv == nullptr || argc < 2) {
        return {};
    }
    return std::span{argv, argc}.subspan(1);
}

}  // namespace

ProcessArgs::ProcessArgs() {
    int count = 0;
    m_Argv = CommandLineToArgvW(GetCommandLineW(), &count);
    if (m_Argv != nullptr) {
        m_Argc = static_cast<size_t>(count);
    }
}

ProcessArgs::~ProcessArgs() noexcept(true) {
    if (m_Argv != nullptr) {
        LocalFree(static_cast<void*>(m_Argv));
    }
}

bool ProcessArgs::is_first(std::string_view arg) const {
    const std::span<wchar_t*> args = user_args(m_Argv, m_Argc);
    return !args.empty() && equals_icase(args.front(), widen(arg));
}

bool ProcessArgs::contains(std::string_view arg) const {
    const std::wstring wide = widen(arg);
    return std::ranges::any_of(user_args(m_Argv, m_Argc), [&wide](const wchar_t* current) {
        return equals_icase(current, wide);
    });
}

}  // namespace blcore::util
