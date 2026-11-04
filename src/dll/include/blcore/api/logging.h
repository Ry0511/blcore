#ifndef BLCORE_API_LOGGING_H
#define BLCORE_API_LOGGING_H

#include "blcore/api/api.h"
#include "blcore/blcore.h"

namespace blcore::logging {

enum class Level : uint8_t {
    Misc = 0,
    Info = 1,
    Warn = 2,
    Debug = 3,
    Error = 4,
};

}  // namespace blcore::logging

BLCORE_API_FN(void, blcore_log, blcore::logging::Level level, const char* msg, size_t len);
BLCORE_API_FN(void, blcore_log_wide, blcore::logging::Level level, const wchar_t* msg, size_t len);

#endif  // BLCORE_API_LOGGING_H
