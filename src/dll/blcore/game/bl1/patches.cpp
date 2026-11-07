#include "blcore/pch.h"

#include <libhat.hpp>

#include "blcore/game/bl1/game_impl.h"
#include "blcore/util/logging.h"
#include "blcore/util/sigscan.h"

namespace blcore::game::bl1 {

////////////////////////////////////////////////////////////////////////////////
// | PRIVATE |
////////////////////////////////////////////////////////////////////////////////

namespace {

constexpr auto SHA_VERIFICATION_SIG = hat::compile_signature<
    " ?? 7C 24 08 00"  // cmp dword [esp + 8], 0 <- ret
    " B9 ?? ?? ?? ??"  // mov ecx, "Missing hash"
    " 75 05"           // jnz
    " B9 ?? ?? ?? ??"  // mov ecx, "Bad hash"
    " 8B 44 24 04"     // mov eax, [esp + 4]
    " 85 C0"           // test eax, eax
    " 75 05"           // jnz
    " B8 ?? ?? ?? ??"  // mov eax, "Unknown file"
    " 51"              // push ecx
    " 50"              // push eax
    " A1 ?? ?? ?? ??"  // mov eax, [GError]
    " 68 ?? ?? ?? ??"  // push "SHA Verification failed for '%s'. Reason: %s"
    " 50"              // push eax
    " E8"              // call
    >();

void patch_sha_verification() {
    const sigscan::ScanResult sha_verification = sigscan::find_for_rw(SHA_VERIFICATION_SIG);

    if (sha_verification.has_result() && sha_verification.write(0, 0xC3)) {
        return;
    }

    BLCORE_WARN("failed to patch SHA verification - modified base game script packages will error");
}

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// | PUBLIC |
////////////////////////////////////////////////////////////////////////////////

void GameImpl::apply_patches() const {
    patch_sha_verification();
}

}  // namespace blcore::game::bl1
