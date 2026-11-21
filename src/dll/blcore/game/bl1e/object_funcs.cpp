#include "blcore/pch.h"

#include <libhat.hpp>

#include "blcore/game/bl1e/game_impl.h"
#include "blcore/util/sigscan.h"

namespace blcore::game::bl1e {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

constexpr auto STATIC_FIND_OBJECT_SIG = hat::compile_signature<
    " 40 55"                       // push rbp
    " 56"                          // push rsi
    " 57"                          // push rdi
    " 41 54"                       // push r12
    " 41 55"                       // push r13
    " 41 56"                       // push r14
    " 41 57"                       // push r15
    " 48 83 EC 70"                 // sub rsp, 0x70
    " 48 C7 44 24 40 FE FF FF FF"  // mov qword [rsp + 0x40], -2
    " 48 89 9C 24 B0 00 00 00"     // mov [rsp + 0xb0], rbx
    " 45 8B E9"                    // mov r13d, r9d (ExactClass)
    >();

constexpr auto STATIC_LOAD_OBJECT_SIG = hat::compile_signature<
    " 48 8B C4"                 // mov rax, rsp
    " 4C 89 48 20"              // mov [rax + 0x20], r9
    " 4C 89 40 18"              // mov [rax + 0x18], r8
    " 48 89 50 10"              // mov [rax + 0x10], rdx
    " 48 89 48 08"              // mov [rax + 0x8], rcx
    " 53"                       // push rbx
    " 56"                       // push rsi
    " 57"                       // push rdi
    " 48 81 EC 10 01 00 00"     // sub rsp, 0x110
    " 48 C7 40 D8 FE FF FF FF"  // mov qword [rax - 0x28], -2
    " 4D 8B C8"                 // mov r9, r8
    " 33 DB"                    // xor ebx, ebx
    " 89 5C 24 40"              // mov [rsp + 0x40], ebx
    " 4D 85 C0"                 // test r8, r8 (Name)
    " 74 ??"                    // jz
    " 66 41 39 18"              // cmp [r8], bx
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

}  // namespace blcore::game::bl1e
