#ifndef BLCORE_COMMON_H
#define BLCORE_COMMON_H

#include "blcore/blcore.h"
#include "blcore/util/logging.h"

#include <exception>
#include <string_view>
#include <utility>

namespace blcore::util {

fs::path module_dir(void* module);

void* load_library(const fs::path& path);

void* get_proc_address(void* module, const char* name);

void free_library(void* module);

std::string narrow(std::wstring_view str);

std::wstring widen(std::string_view str);

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

}  // namespace blcore::util

#endif  // BLCORE_COMMON_H
