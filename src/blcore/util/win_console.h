#ifndef BLCORE_WIN_CONSOLE_H
#define BLCORE_WIN_CONSOLE_H

#include "blcore/blcore.h"

#include <string_view>

namespace blcore {

class WinConsole {
   public:
    WinConsole();
    ~WinConsole();

    WinConsole(const WinConsole&) = delete;
    WinConsole(WinConsole&&) = delete;
    WinConsole& operator=(const WinConsole&) = delete;
    WinConsole& operator=(WinConsole&&) = delete;

    void write(std::string_view text) const;

   private:
    void* handle = nullptr;
    bool allocated = false;
};

}  // namespace blcore

#endif  // BLCORE_WIN_CONSOLE_H
