#ifndef BLCORE_LOGGING_H
#define BLCORE_LOGGING_H

#include "blcore/blcore.h"

namespace blcore::logging {

enum class Level : uint8_t {
    Misc,
    Info,
    Warn,
    Debug,
    Error,
};

void initialise();
void terminate();

void set_console_logging(bool enabled);
void add_log_file(const fs::path& out, bool append = false);

void log(Level level, const std::string& msg);
void log(Level level, const std::wstring& msg);

}  // namespace blcore::logging

#endif  // BLCORE_LOGGING_H
