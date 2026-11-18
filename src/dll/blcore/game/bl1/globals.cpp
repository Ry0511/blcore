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

}  // namespace blcore::game::bl1
