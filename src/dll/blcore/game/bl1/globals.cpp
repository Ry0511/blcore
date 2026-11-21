#include "blcore/pch.h"

#include <libhat.hpp>

#include "blcore/game/bl1/game_impl.h"
#include "blcore/util/sigscan.h"

namespace blcore::game::bl1 {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

constexpr size_t GOBJECTS_OFFSET = 2;
constexpr auto GOBJECTS_SIG = hat::compile_signature<
    " 8B 0D ?? ?? ?? ??"  // mov ecx, [GObjObjects]
    " 8B 04 ??"           // mov eax, [ecx + esi*4]
    " 8B 50 ??"           // mov edx, [eax + 0xc]
    " 21 58 ??"           // and [eax + 8], ebx
    " 89 50 ??"           // mov [eax + 0xc], edx
    >();

constexpr size_t GNAMES_OFFSET = 1;
constexpr auto GNAMES_SIG = hat::compile_signature<
    " A1 ?? ?? ?? ??"  // mov eax, [Names]
    " 8B 0C ??"        // mov ecx, [eax + esi*4]
    " 68 ?? ?? ?? ??"  // push 0x1000
    " 6A ??"           // push 0
    " E8 ?? ?? ?? ??"  // call
    " 5E"              // pop esi
    >();

constexpr size_t GMALLOC_OFFSET = 2;
constexpr auto GMALLOC_SIG = hat::compile_signature<
    " 89 0D ?? ?? ?? ??"  // mov [GMalloc], ecx
    " 8B 11"              // mov edx, [ecx]
    >();

constexpr size_t GNATIVES_OFFSET = 3;
constexpr auto GNATIVES_SIG = hat::compile_signature<
    " 8B 14 95 ?? ?? ?? ??"  // mov edx, [edx*4 + GNatives]
    " 57"                    // push edi
    " 8D 4D ??"              // lea ecx, [ebp - 0x44]
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

}  // namespace blcore::game::bl1
