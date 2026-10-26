#ifndef BLCORE_COMMON_H
#define BLCORE_COMMON_H

#include "blcore/blcore.h"

#include <string_view>

namespace blcore::util {

fs::path module_dir(void* module);

std::string narrow(std::wstring_view str);

std::wstring widen(std::string_view str);

}  // namespace blcore::util

#endif  // BLCORE_COMMON_H
