#include "blcore/pch.h"

#include <libhat.hpp>

#include "blcore/game/bl1e/game_impl.h"

namespace blcore::game::bl1e {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

constexpr auto ENTRY_SIG = hat::compile_signature<
    " 48 8B D8"        // mov rbx, rax
    " 48 83 38 00"     // cmp qword [rax], 0
    " 74 ??"           // jz
    " 48 8B C8"        // mov rcx, rax
    " E8 ?? ?? ?? ??"  // call __scrt_is_nonwritable_in_current_image
    " 84 C0"           // test al, al
    >();

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

std::string_view GameImpl::name() const {
    return "BL1E";
}

bool GameImpl::is_unpacked() const {
    return hat::find_pattern(ENTRY_SIG, ".text").has_result();
}

}  // namespace blcore::game::bl1e
