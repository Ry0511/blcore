#include "blcore/pch.h"

#include "blcore/game/game.h"

namespace blcore::game {

namespace {

Globals found{};

}  // namespace

void init_globals() {
    find_globals(found);
}

const Globals& globals() {
    return found;
}

}  // namespace blcore::game
