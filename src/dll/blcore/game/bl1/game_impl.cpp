#include "blcore/pch.h"

#include <libhat.hpp>

#include "blcore/game/bl1/game_impl.h"

namespace blcore::game::bl1 {

std::string_view GameImpl::name() const {
    return "Borderlands (Steam/UDK)";
}

bool GameImpl::is_unpacked() const {
    constexpr auto ENTRY_SIG = hat::compile_signature<
        " 6A 58"           // push 0x58
        " 68 ?? ?? ?? ??"  // push <__tmainCRTStartup scope table>
        " E8 ?? ?? ?? ??"  // call __SEH_prolog4
        " 33 DB"           // xor ebx, ebx
        >();
    return hat::find_pattern(ENTRY_SIG, ".text").has_result();
}

}  // namespace blcore::game::bl1
