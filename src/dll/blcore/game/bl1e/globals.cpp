#include "blcore/pch.h"

#include "blcore/game/bl1e/game_impl.h"
#include "blcore/util/logging.h"

namespace blcore::game::bl1e {

void GameImpl::find_globals(Globals& /*out*/) const {
    BLCORE_WARN("Engine globals aren't mapped for BL1E yet");
}

}  // namespace blcore::game::bl1e
