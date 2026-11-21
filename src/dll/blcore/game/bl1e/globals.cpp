#include "blcore/pch.h"

#include <libhat.hpp>

#include "blcore/game/bl1e/game_impl.h"
#include "blcore/util/sigscan.h"

namespace blcore::game::bl1e {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

constexpr size_t GOBJECTS_OFFSET = 9;
constexpr auto GOBJECTS_SIG = hat::compile_signature<
    " 8B 0D ?? ?? ?? ??"     // mov ecx, [GObjObjects.ArrayNum]
    " 48 8B 15 ?? ?? ?? ??"  // mov rdx, [GObjObjects] <- offset
    " 48 83 3C DA 00"        // cmp qword [rdx + rbx*8], 0
    >();

constexpr size_t GNAMES_OFFSET = 8;
constexpr auto GNAMES_SIG = hat::compile_signature<
    " E8 ?? ?? ?? ??"        // call
    " 48 8B 05 ?? ?? ?? ??"  // mov rax, [Names] <- offset
    " 48 89 3C D8"           // mov [rax + rbx*8], rdi
    " 49 8B CC"              // mov rcx, r12
    " FF 15 ?? ?? ?? ??"     // call [LeaveCriticalSection]
    >();

constexpr size_t GMALLOC_OFFSET = 5;
constexpr auto GMALLOC_SIG = hat::compile_signature<
    " 33 FF"                 // xor edi, edi
    " 48 89 3D ?? ?? ?? ??"  // mov [GMalloc], rdi <- offset
    " 48 8B 7C 24 38"        // mov rdi, [rsp + 0x38]
    >();

constexpr size_t GNATIVES_OFFSET = 28;
constexpr auto GNATIVES_SIG = hat::compile_signature<
    " 33 C9"                 // xor ecx, ecx
    " 48 39 15 ?? ?? ?? ??"  // cmp [GNatives], rdx
    " 0F 45 C1"              // cmovnz eax, ecx
    " 89 05 ?? ?? ?? ??"     // mov [..], eax
    " 48 8B 05 ?? ?? ?? ??"  // mov rax, [..]
    " 48 89 05 ?? ?? ?? ??"  // mov [GNatives], rax <- offset
    " C3"                    // ret
    >();

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

void GameImpl::find_globals() {
    m_AddressTable.gobjects = sigscan::find_global<void>("GObjects", GOBJECTS_SIG, GOBJECTS_OFFSET);
    m_AddressTable.gnames = sigscan::find_global<void>("GNames", GNAMES_SIG, GNAMES_OFFSET);
    m_AddressTable.gmalloc = sigscan::find_global<void>("GMalloc", GMALLOC_SIG, GMALLOC_OFFSET);
    m_AddressTable.gnatives = sigscan::find_global<void>("GNatives", GNATIVES_SIG, GNATIVES_OFFSET);
}

}  // namespace blcore::game::bl1e
