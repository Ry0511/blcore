#ifndef BLCORE_UE3_GLOBALS_H
#define BLCORE_UE3_GLOBALS_H

#include "blcore/game/game.h"

namespace blcore::ue3 {

void find_globals();

const game::Globals& found_globals();

}  // namespace blcore::ue3

#endif  // BLCORE_UE3_GLOBALS_H
