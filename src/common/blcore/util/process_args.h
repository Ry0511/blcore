#ifndef BLCORE_PROCESS_ARGS_H
#define BLCORE_PROCESS_ARGS_H

#include "blcore/blcore.h"

#include <string_view>

namespace blcore::util {

class ProcessArgs {
   public:
    explicit ProcessArgs();
    ~ProcessArgs() noexcept(true);

    ProcessArgs(const ProcessArgs&) = delete;
    ProcessArgs(ProcessArgs&&) = delete;
    ProcessArgs& operator=(const ProcessArgs&) = delete;
    ProcessArgs& operator=(ProcessArgs&&) = delete;

    // case insensitive
    bool is_first(std::string_view arg) const;
    bool contains(std::string_view arg) const;

    bool is_make_commandlet() const { return is_first("make"); }
    bool is_editor() const { return contains("-editor"); }
    bool is_game() const { return !is_make_commandlet() && !is_editor(); }

   private:
    wchar_t** m_Argv{nullptr};
    size_t m_Argc{0};
};

}  // namespace blcore::util

#endif  // BLCORE_PROCESS_ARGS_H
