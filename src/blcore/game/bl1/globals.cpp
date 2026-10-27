#include "blcore/pch.h"

#ifdef WILLOW

#include <libhat.hpp>

#include "blcore/game/game.h"
#include "blcore/util/sigscan.h"

namespace blcore::game {

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

void find_globals(Globals& out) {
    out.gobjects = sigscan::find_absolute_address<ue3::TArray<void*>>("GObjects", GOBJECTS_SIG, GOBJECTS_OFFSET);
    out.gnames = sigscan::find_absolute_address("GNames", GNAMES_SIG, GNAMES_OFFSET);
    out.gmalloc = sigscan::find_absolute_address("GMalloc", GMALLOC_SIG, GMALLOC_OFFSET);
    out.gnatives = sigscan::find_absolute_address("GNatives", GNATIVES_SIG, GNATIVES_OFFSET);
}

}  // namespace blcore::game

#endif  // WILLOW
