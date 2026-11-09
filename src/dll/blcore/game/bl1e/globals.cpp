#include "blcore/pch.h"

#include <libhat.hpp>

#include "blcore/game/bl1e/game_impl.h"
#include "blcore/util/logging.h"
#include "blcore/util/sigscan.h"

namespace blcore::game::bl1e {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

// UObject* UObject::StaticFindObject(UClass* Class, UObject* InOuter, const TCHAR* Name, UBOOL ExactClass)
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

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

void GameImpl::find_globals() {
    BLCORE_WARN("GObjects, GNames, GMalloc and GNatives aren't mapped for BL1E yet");
    m_StaticFindObject = reinterpret_cast<StaticFindObjectFn>(
        sigscan::find("StaticFindObject", STATIC_FIND_OBJECT_SIG)
    );
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

Game::StaticFindObjectFn GameImpl::static_find_object() const {
    return m_StaticFindObject;
}

}  // namespace blcore::game::bl1e
