#include "blcore/pch.h"

#include "blcore/game/game.h"
#include "blcore/api/gnames.h"

BLCORE_API_FN(blcore::ue3::TArray<blcore::ue3::FNameEntry*>*, blcore_get_gnames) {
    return blcore::game::globals().gnames;
}
