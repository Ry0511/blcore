#include "blcore/pch.h"

#include "blcore/game/bl1/game_impl.h"
#include "blcore/game/bl1e/game_impl.h"
#include "blcore/game/game.h"

namespace blcore::game {

// this is fine for now since we only care about these two
Game& current() {
#ifdef WILLOW
    static bl1::GameImpl instance{};
#elifdef WILLOW64
    static bl1e::GameImpl instance{};
#endif
    return instance;
}

}  // namespace blcore::game
