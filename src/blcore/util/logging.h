#ifndef BLCORE_UTIL_LOGGING_H
#define BLCORE_UTIL_LOGGING_H

#include "blcore/api/logging.h"

#include <format>
#include <string_view>

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

namespace blcore::logging {

inline void log(Level level, std::string_view msg) {
    blcore_log(level, msg.data(), msg.size());
}

inline void log(Level level, std::wstring_view msg) {
    blcore_log_wide(level, msg.data(), msg.size());
}

}  // namespace blcore::logging

// NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define BLCORE_LOG(level, ...)           \
    ::blcore::logging::log(              \
        ::blcore::logging::Level::level, \
        ::std::format(__VA_ARGS__)       \
    )

#define BLCORE_MISC(...) BLCORE_LOG(Misc, __VA_ARGS__)
#define BLCORE_INFO(...) BLCORE_LOG(Info, __VA_ARGS__)
#define BLCORE_WARN(...) BLCORE_LOG(Warn, __VA_ARGS__)
#define BLCORE_DEBUG(...) BLCORE_LOG(Debug, __VA_ARGS__)
#define BLCORE_ERROR(...) BLCORE_LOG(Error, __VA_ARGS__)

// NOLINTEND(cppcoreguidelines-macro-usage)

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

#ifdef BLCORE_EXPORTS

#include "blcore/blcore.h"

namespace blcore::logging {

void initialise();
void terminate();

void set_console_logging(bool enabled);
void add_log_file(const fs::path& out, bool append = false);

}  // namespace blcore::logging

#endif  // BLCORE_EXPORTS

#endif  // BLCORE_UTIL_LOGGING_H
