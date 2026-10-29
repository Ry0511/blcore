#ifndef BLCORE_API_LOGGING_H
#define BLCORE_API_LOGGING_H

#include "blcore/api/api.h"

#include <cstddef>
#include <cstdint>

namespace blcore::logging {

enum class Level : std::uint8_t {
    Misc = 0,
    Info = 1,
    Warn = 2,
    Debug = 3,
    Error = 4,
};

}  // namespace blcore::logging

BLCORE_API_FN(void, blcore_log, blcore::logging::Level level, const char* msg, std::size_t len);
BLCORE_API_FN(void, blcore_log_wide, blcore::logging::Level level, const wchar_t* msg, std::size_t len);

#endif  // BLCORE_API_LOGGING_H
