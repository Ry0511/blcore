#include "blcore/pch.h"

#include <libhat.hpp>

#include "blcore/game/bl1/game_impl.h"

namespace blcore::game::bl1 {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

constexpr auto ENTRY_SIG = hat::compile_signature<
    " 6A 58"           // push 0x58
    " 68 ?? ?? ?? ??"  // push <__tmainCRTStartup scope table>
    " E8 ?? ?? ?? ??"  // call __SEH_prolog4
    " 33 DB"           // xor ebx, ebx
    >();

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

std::string_view GameImpl::name() const {
    return "Borderlands (Steam/UDK)";
}

bool GameImpl::is_unpacked() const {
    return hat::find_pattern(ENTRY_SIG, ".text").has_result();
}

const AddressTable& GameImpl::address_table() const {
    return m_AddressTable;
}

void GameImpl::initialise() {
    find_globals();
    find_static_find_object();
    find_static_load_object();
    apply_sha_bypass();
}

}  // namespace blcore::game::bl1
