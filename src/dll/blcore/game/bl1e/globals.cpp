#include "blcore/pch.h"

#ifdef WILLOW64

#include "blcore/game/game.h"
#include "blcore/util/logging.h"

namespace blcore::game {

void find_globals(Globals& /*out*/) {
    BLCORE_WARN("Engine globals aren't mapped for BL1E yet");
}

}  // namespace blcore::game

#endif  // WILLOW64
