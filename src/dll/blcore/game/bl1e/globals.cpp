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

void GameImpl::find_globals() {
    m_GObjects = sigscan::find_global<ue3::TArray<ue3::UObject*>>(
        "GObjects",
        GOBJECTS_SIG,
        GOBJECTS_OFFSET
    );
    m_GNames = sigscan::find_global<ue3::TArray<ue3::FNameEntry*>>(
        "GNames",
        GNAMES_SIG,
        GNAMES_OFFSET
    );
    m_GMalloc = sigscan::find_global<ue3::FMalloc*>("GMalloc", GMALLOC_SIG, GMALLOC_OFFSET);
    m_GNatives = sigscan::find_global("GNatives", GNATIVES_SIG, GNATIVES_OFFSET);
    m_EngineFunctions.static_find_object = sigscan::find("StaticFindObject", STATIC_FIND_OBJECT_SIG);
    m_EngineFunctions.static_load_object = sigscan::find("StaticLoadObject", STATIC_LOAD_OBJECT_SIG);
}

engine::GObjects GameImpl::gobjects() const {
    return engine::GObjects{m_GObjects};
}

engine::GNames GameImpl::gnames() const {
    return engine::GNames{m_GNames};
}

engine::GMalloc GameImpl::gmalloc() const {
    return engine::GMalloc{m_GMalloc};
}

const EngineFunctions& GameImpl::engine_functions() const {
    return m_EngineFunctions;
}

}  // namespace blcore::game::bl1e
