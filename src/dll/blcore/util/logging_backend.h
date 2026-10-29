#ifndef BLCORE_UTIL_LOGGING_BACKEND_H
#define BLCORE_UTIL_LOGGING_BACKEND_H

#include "blcore/blcore.h"

namespace blcore::logging {

void initialise();
void terminate(bool wait = false);

void set_console_logging(bool enabled);
void add_log_file(const fs::path& out, bool append = false);

}  // namespace blcore::logging

#endif  // BLCORE_UTIL_LOGGING_BACKEND_H
