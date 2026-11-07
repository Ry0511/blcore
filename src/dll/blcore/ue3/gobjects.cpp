#include "blcore/pch.h"

#include "blcore/api/gobjects.h"
#include "blcore/game/game.h"

BLCORE_API_FN(blcore::ue3::TArray<blcore::ue3::UObject*>*, blcore_get_gobjects) {
    return blcore::game::current().globals().gobjects;
}
