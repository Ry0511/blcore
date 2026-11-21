#include "blcore/pch.h"

#include <libhat.hpp>

#include "blcore/game/bl1/game_impl.h"
#include "blcore/util/sigscan.h"

namespace blcore::game::bl1 {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

constexpr auto STATIC_FIND_OBJECT_SIG = hat::compile_signature<
    " 6A FF"              // push -1
    " 68 ?? ?? ?? ??"     // push handler
    " 64 A1 ?? ?? ?? ??"  // mov eax, fs:[0]
    " 50"                 // push eax
    " 83 EC 24"           // sub esp, 0x24
    " 53"                 // push ebx
    " 55"                 // push ebp
    " 56"                 // push esi
    " 57"                 // push edi
    " A1 ?? ?? ?? ??"     // mov eax, [security_cookie]
    " 33 C4"              // xor eax, esp
    " 50"                 // push eax
    " 8D 44 24 ??"        // lea eax, [esp + 0x38]
    " 64 A3 ?? ?? ?? ??"  // mov fs:[0], eax
    " 8B 74 24 ??"        // mov esi, [esp + 0x4c] (InOuter)
    " 8B 7C 24 ??"        // mov edi, [esp + 0x50] (Name)
    >();

constexpr auto STATIC_LOAD_OBJECT_SIG = hat::compile_signature<
    " 55"                 // push ebp
    " 8B EC"              // mov ebp, esp
    " 6A FF"              // push -1
    " 68 ?? ?? ?? ??"     // push handler
    " 64 A1 00 00 00 00"  // mov eax, fs:[0]
    " 50"                 // push eax
    " 83 EC 68"           // sub esp, 0x68
    " 53"                 // push ebx
    " 56"                 // push esi
    " 57"                 // push edi
    " A1 ?? ?? ?? ??"     // mov eax, [security_cookie]
    " 33 C5"              // xor eax, ebp
    " 50"                 // push eax
    " 8D 45 F4"           // lea eax, [ebp - 0xc]
    " 64 A3 00 00 00 00"  // mov fs:[0], eax
    " 89 65 F0"           // mov [ebp - 0x10], esp
    " 8B 75 10"           // mov esi, [ebp + 0x10] (Name)
    " 33 FF"              // xor edi, edi
    " 89 7D EC"           // mov [ebp - 0x14], edi
    " 3B F7"              // cmp esi, edi
    " 74"                 // jz
    >();

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

void GameImpl::find_static_find_object() {
    m_AddressTable.static_find_object = sigscan::find("StaticFindObject", STATIC_FIND_OBJECT_SIG);
}

void GameImpl::find_static_load_object() {
    m_AddressTable.static_load_object = sigscan::find("StaticLoadObject", STATIC_LOAD_OBJECT_SIG);
}

}  // namespace blcore::game::bl1
