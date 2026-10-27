#include "blcore/pch.h"

#include "blcore/game/game.h"
#include "blcore/ue3/globals.h"

namespace blcore::ue3 {

namespace {

game::Globals found{};

}  // namespace

void find_globals() {
    game::find_globals(found);
}

const game::Globals& found_globals() {
    return found;
}

}  // namespace blcore::ue3
