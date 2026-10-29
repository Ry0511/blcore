#ifndef BLCORE_UTIL_SIGSCAN_H
#define BLCORE_UTIL_SIGSCAN_H

#include "blcore/util/logging.h"

#include <libhat.hpp>

#include <cstddef>
#include <cstring>
#include <string_view>

namespace blcore::sigscan {

template <typename T = void*, typename Signature>
T* find_absolute_address(std::string_view name, const Signature& signature, std::size_t offset) {
    const auto result = hat::find_pattern(signature, ".text");
    if (!result.has_result()) {
        BLCORE_ERROR("Failed to find {}", name);
        return nullptr;
    }

    T* address = nullptr;
    std::memcpy(static_cast<void*>(&address), result.get() + offset, sizeof(T*));
    BLCORE_INFO("Found {} at {}", name, static_cast<const void*>(address));
    return address;
}

}  // namespace blcore::sigscan

#endif  // BLCORE_UTIL_SIGSCAN_H
